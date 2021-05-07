//
// Created by eduardo218 on 4/5/21.
//

#ifndef C__SERVER_MEMORYMANAGEMENT_H
#define C__SERVER_MEMORYMANAGEMENT_H

#include "../DataStructures/Queue.h"
#include "../Types/GenericType.h"
#include "../Util/Converter.h"
#include "../../librerias/spdlog/spdlog.h"

class MemoryManagement {

private:
    static MemoryManagement *instance;

    /** Actual offset of the memory block, its the last position available, used for adding new objects when theres no offsets for recycling.*/
    int offset;
    /** Queue of memory offsets that can be used for recycling, when deleting an element from the server, the offset its added here*/
    Queue<int> *availableAddresses;
    /** Pointer to the first memory address of the memory block created with malloc, used to make pointer arithmetics.*/
    void *baseDir;
    /** Memory map of the server, stores GenericType instances.*/
    LinkedList<GenericType *> *map;

    /**
     * Method for adding an element to the memory block.
     * @tparam T type of the element, used to cast the void* pointer, in order to use arithmetics.
     * @param element element to add.
     * @return offset used to add the new element.
     */
    template<typename T>
    int addElement(T element) {
        int address;
        //caso en que no hay para reciclar
        if (availableAddresses->isEmpty()) {
            T *temp = (T *) baseDir;
            *(temp + offset) = element;
            address = offset;
            offset++;
        } else {
            availableAddresses->show();
            int position = availableAddresses->peek();
            T *temp = (T *) baseDir;
            *(temp + position) = element;
            address = position;
            spdlog::info("El elemento: " + to_string(element) + " fué guardado en la posición (reutilizada): " +
                         to_string(position));
            availableAddresses->deQueue();
        }
        return address;
    }

public:
    MemoryManagement(int size) {
        //create malloc of the custom size.
        this->baseDir = malloc(size);
        //Initialize variables
        this->availableAddresses = new Queue<int>();
        this->map = new LinkedList<GenericType *>();
        this->offset = 1;
    }

/**
 * Method for getting an element, given the position in the memory block *THE MEMORY BLOCK SAVES ELEMENTS IN 1-BASED INDEX*
 * @tparam T Type of the element to get, its for the casting to the correct type the pointer.
 * @param i 1-based index of the element to get.
 * @return element from the memory block, in the position i.
 */
    template<typename T>
    T get(int i) {
        T *dir = (T *) baseDir;
        return *(dir + i);
    }

/**
 * Method used for modifying an memory address.
 * @tparam T type of the new value to store on the memory address.
 * @param i offset of the memory address.
 * @param value to store.
 */
    template<typename T>
    void modify(int i, T value) {
        T *dir = (T *) baseDir;
        *(dir + i) = value;

    }

/**
 * Method for showing in the console the memory map and the memory block with its elements.
 */
    void show() {
        if (this->map->getLen() == 0) {
            cout << "**** MAP EMPTY ****" << endl;
            return;
        }
        updateVariables();
        cout << "\n\n-------Memory Map---------\n";
        int i = 0;
        while (i < this->map->getLen()) {
            GenericType *obj = map->get(i);
            string VAL = obj->getValue();
            cout << "Name: " << obj->getKey()
                 << " | Offset: " << obj->getOffset()
                 << " | Value: " << VAL
                 << " | Type: " << obj->getType()
                 << " | Counter: " << obj->getCounter()
                 << "\n-------------------" << endl;
            i++;
        }

        cout << "-------Memory Block---------\n";
        for (int j = 1; j < offset; ++j) {
            cout << "Position: " << j << " | Value (Int): " << this->get<int>(j)
                 << " | Value (Float): " << this->get<float>(j)
                 << " | Value (Double): " << this->get<double>(j)
                 << " | Value (Long): " << this->get<long>(j)
                 << " | Value (Char): " << this->get<char>(j) << endl
                 << "\n-------------------" << endl;
        }
    }

public:
    /**
     * Method for getting an element from the memory map.
     * @param key name of the variable, this value doesnt repeat, and its used as unique search key
     * @return GenericType object if found. nullptr if the element is not in the memory map.
     */
    GenericType *getElement(const string &key) {
        updateVariables();
        GenericType *temp = nullptr;
        for (int i = 0; i < map->getLen(); ++i) {
            if (map->get(i)->getKey() == key) {
                temp = map->get(i);
            }
        }
        return temp;

    }

    /**
     * Method for operating two values stored in the memory map.
     * @tparam T type of the values (important because it casts the result and must be the same type of value)
     * @param object_1 name of the first value.
     * @param object_2 name of the second value.
     * @param operator_used operator to use.
     * @return Log message of the result.
     */
    template<typename T>
    string operate(string object_1, string object_2, string operator_used, Response *resp) {
        cerr << "Operator: " << operator_used << endl;
        //todo: caso cuando el segundo valor es un numero o un elemento :)
        GenericType *obj_1 = getElement(object_1);
        GenericType *obj_2 = getElement(object_2);
        int offset_obj_1 = obj_1->getOffset();
        int offset_obj_2 = obj_2->getOffset();

        T value1 = get<T>(offset_obj_1);
        T value2 = get<T>(offset_obj_2);
        string result_log;

        if (operator_used == "=") {
            modify<T>(offset_obj_1, value2);
            result_log = object_1 + LOG_VARIABLE_MODIFYIED + to_string(value2);
            obj_1->setValue(to_string(value2));
        }
        if (operator_used == "+") {
            T sum = (value2 + value1);
            modify<T>(offset_obj_1, sum);
            result_log = object_1 + LOG_VARIABLE_MODIFYIED + to_string((value2 + value1));
            obj_1->setValue(to_string((value2 + value1)));

        }
        resp->setLog(result_log);
    }

    /**
     * Method for getting the memory address of an GenericType object in the memory map.
     * @param key name of the variable.
     * @return memory address of the object, in string format.
     */
    string getAddr(const string &key) {
        return this->getElement(key)->getAddr();
    }

/**
 * Method for adding numeric objects to the memory, it is separated from numeric and char, because of the casting of a void* pointer.
 * It would not compile otherwise.
 * @tparam T type of the object (int, float, double, long)
 * @param obj_to_add pointer to the element to add to the server.
 * @return json format of the element added.
 */
    template<typename T>
    string addElementDigits(GenericType *obj_to_add) {
        if (this->getElement(obj_to_add->getKey()))return "";
        T element = Converter::convertDigits<T>(obj_to_add->getValue().c_str());
        int obj_offset = this->addElement<T>(element);
        T *casted_dir = (T *) baseDir;

        //Cast the la dirección de memoria a const char*
        std::ostringstream address;
        address << ((casted_dir + obj_offset));
        const char *addr = address.str().c_str();

        obj_to_add->setAddr(addr);
        obj_to_add->setOffset(obj_offset);
        obj_to_add->setReferenceCount(1);
        //agrego el objeto en el mapa de memoruia
        const string &jsonGenerated = Json::generateJson(obj_to_add);
        this->map->append(obj_to_add);
        //spdlog::info("Variable created: " + jsonGenerated);
        return jsonGenerated;
    }

    /**
     * Specific case for adding a Char, same as addElementDigit but the casting is different.
     * @param obj_to_add pointer to the object to add.
     * @return Json of the generated object.
     */
    string addElementChar(GenericType *obj_to_add) {
        int dir = this->addElement<char>(*obj_to_add->getValue().c_str());
        //le asigno a el objeto el valor, para poder accesarlo luego.
        obj_to_add->setOffset(dir);
        obj_to_add->setReferenceCount(1);
        //agrego el objeto en el mapa de memoria
        this->map->append(obj_to_add);
        return Json::generateJson(obj_to_add);
    }

    //fixme: TEST AND IMPLEMENT.
    void deleteElement(int key) {
        GenericType *obj = this->map->get(key);
        long *temp = (long *) this->baseDir;

        long *ptr = temp + obj->getOffset();
        //free(ptr);

        this->map->del(obj);
        this->availableAddresses->queue(obj->getOffset());
        this->map->del(obj);
        spdlog::info("Deleted: " + obj->getKey());
    }

    /**
     * Method for updating the value of an object in an memory map, using the value from the memory array.
     * It uses the type for getting the element in the right type of cast.
     * @param obj_to_update pointer to the object to update.
     */
    void uptadeVariables_aux(GenericType *obj_to_update) {

        if (obj_to_update->getType() == INTEGER_KEY_WORD) {
            auto var = get<int>(obj_to_update->getOffset());
            string value = std::to_string(var);
            obj_to_update->setValue(value);
        } else if (obj_to_update->getType() == DOUBLE_KEY_WORD) {
            auto var = get<double>(obj_to_update->getOffset());
            obj_to_update->setValue(std::to_string(var).c_str());
        } else if (obj_to_update->getType() == FLOAT_KEY_WORD) {
            auto var = get<float>(obj_to_update->getOffset());
            obj_to_update->setValue(std::to_string(var).c_str());
        } else if (obj_to_update->getType() == LONG_KEY_WORD) {
            auto var = get<long>(obj_to_update->getOffset());
            obj_to_update->setValue(std::to_string(var).c_str());
        } else if (obj_to_update->getType() == CHAR_KEY_WORD) {
            auto var = get<char>(obj_to_update->getOffset());
            obj_to_update->setValue(std::to_string(var).c_str());
        } else if (obj_to_update->getType() == INTEGER_KEY_WORD) {
            cout << "Struct not implemented." << endl;
        } else if (obj_to_update->getType() == INTEGER_KEY_WORD) {
            cout << "Struct not implemented." << endl;

        }
    }

    /**
     * Main method for updating variables on the memory, runs "uptadeVariables_aux" for all the elements on the memory map.
     */
    void updateVariables() {
        for (int i = 0; i < this->map->getLen(); i++) {
            GenericType *update = this->map->get(i);
            this->uptadeVariables_aux(update);
        }
    }

    void addReferenceCount(string basicString) {
        GenericType *obj = this->getElement(basicString);
        obj->setReferenceCount(obj->getReferenceCount() + 1);

    }

    void __cleanMemory() {
        for (int i = 0; i < this->map->getLen(); i++) {
            GenericType *obj = this->map->get(i);
            if (obj->getOffset() == 0) {
                spdlog::info("Deleting the object: " + obj->getKey());
                this->deleteElement(i);
            }
        }
    }

    void __halt() {
        cout << "deleting all variables..." << endl;
        for (int i = 0; i < this->map->getLen(); i++) {
            deleteElement(i);
        }
        this->show();
    }
};


#endif //C__SERVER_MEMORYMANAGEMENT_H

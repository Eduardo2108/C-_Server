//
// Created by eduardo218 on 4/5/21.
//

#ifndef C__SERVER_MEMORYMANAGEMENT_H
#define C__SERVER_MEMORYMANAGEMENT_H

#include "DataStructures/Queue.h"
#include "Types/GenericType.h"
#include "Util/Converter.h"

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
            cout << "El elemento: " << element << " fué guardado en la posición: " << offset <<
                 " con un tamaño de: " << sizeof(*(temp + offset)) <<
                 " bytes" << ", en una dirección de memoria de: "
                 << sizeof((temp + offset)) <<
                 " bytes" << endl;
            offset++;
        } else {
            availableAddresses->show();
            int position = availableAddresses->peek();
            T *temp = (T *) baseDir;
            *(temp + position) = element;
            address = position;
            cout << "El elemento: " << element << " fué guardado en la posición (reutilizada): " << position << endl;
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

    template<typename T>
    T modify(int i, T value) {
        T *dir = (T *) baseDir;
        *(dir + i) = value;
    }

    void show() {
        cout << "-------Memory Map---------\n";
        for (int i = 0; i < this->map->getLen(); ++i) {
            GenericType *obj = map->get(i);
            cout << "Name: " << obj->getKey()
                 << " | Offset: " << obj->getOffset()
                 << " | Value: " << obj->getValue()
                 << " | Type: " << obj->getType()
                 << "\n-------------------" << endl;
        }
        cout << "-------Memory Block---------\n";
        for (int i = 1; i < offset; ++i) {
            cout << "Position: " << i << " | Value (Int): " << this->get<int>(i)
                 << " | Value (Float): " << this->get<float>(i)
                 << " | Value (Double): " << this->get<double>(i)
                 << " | Value (Long): " << this->get<long>(i)
                 << " | Value (Char): " << this->get<char>(i) << endl
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
        GenericType *temp = nullptr;
        for (int i = 0; i < map->getLen(); ++i) {
            if (map->get(i)->getKey() == key) {
                temp = map->get(i);
            }
        }
        return temp;

    }

    template<typename T>
    int operateVariable(string key, T var) {
        int position = getElement(key)->getOffset();
        T *temp = (T *) baseDir;
        *(temp + position) = var;
        return 1;
    }

    template<typename T>
    int operate(string key1, string key2, string op) {
        int index_1 = getElement(key1)->getOffset();
        int index_2 = getElement(key2)->getOffset();
        T value1 = get<T>(index_1);
        T value2 = get<T>(index_2);

        if (op == "=")
            modify(index_1, value2);
        if (op == "+")
            modify(index_1, (value2 + value1));
    }

    /**
     * Method for getting the memory address of an GenericType object in the memory map.
     * @param key name of the variable.
     * @return memory address of the object, in string format.
     */
    string getAddr(const string &key) {
        return this->getElement(key)->getAddr();
    }

    template<typename T>
    void addElementDigits(GenericType *obj) {
        auto *conv = new Converter();
        T element = conv->convertDigits<T>(obj->getValue());
        int dir = this->addElement<T>(element);
        //le asigno a el objeto el valor, para poder accesarlo luego.
        obj->setOffset(dir);
        //agrego el objeto en el mapa de memoruia
        this->map->append(obj);
        this->show();
    }

    void addElementChar(GenericType *obj) {
        int dir = this->addElement<char>(*obj->getValue());
        //le asigno a el objeto el valor, para poder accesarlo luego.
        obj->setOffset(dir);
        //agrego el objeto en el mapa de memoruia
        this->map->append(obj);
    }

    void deleteElement(string key) {
        GenericType *obj = this->getElement(key);
        long *temp = (long *) this->baseDir;

        long *ptr = temp + obj->getOffset();
        //free(ptr);

        this->map->del(obj);
        this->availableAddresses->queue(obj->getOffset());
        this->map->del(obj);
    }
};


#endif //C__SERVER_MEMORYMANAGEMENT_H

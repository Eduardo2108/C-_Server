//
// Created by eduardo218 on 4/5/21.
//

#ifndef C__SERVER_MEMORYMANAGER_H
#define C__SERVER_MEMORYMANAGER_H

#include "../DataStructures/Queue.h"
#include "../Types/GenericType.h"

class MemoryManager {
private:
    //Un int que almacena por cual posición del array de memoria se deben agregar elementos
    int offset;
    //una lista que guarda índices para almacenar los valores :)
    Queue<int> *availableAddresses;
    // dirección de memoria del primer bloque de memoria del array de direcciones (malloc)
    void *baseDir;

    LinkedList<GenericType> map;

private:
    template<typename T>
    void addElement(T element) {
        //caso en que no hay para reciclar
        if (availableAddresses->isEmpty()) {
            T *dir = (T *) baseDir;
            *(dir + offset) = element;
            cout << "El elemento: " << element << " fué guardado en la posición: " << offset << endl;
            offset++;
        }
            //caso en que se  recicla.
        else {
            //obtengo el número en el que tengo que agregar el elemento :)
            int position = availableAddresses->peek();
            //Cambio el valor usando arithmetic de punteros  :)
            *(baseDir + position) = element;
            cout << "El elemento: " << element << " fué guardado en la posición: " << position << endl;
            //saco el número de la lista de reciclaje :)
            availableAddresses->deQueue();
        }
    }

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

public:

    GenericType getElement(string key) {
        GenericType temp = nullptr;
        for (int i = 0; i < map.getLen(); ++i) {
            if (map.get(i).getKey() == key) {
                temp = map.get(i);
                break;
            }
        }
        return temp;
    }

    string getAddr(string key) {
        this->getElement(key).getAddr();
    }
};


#endif //C__SERVER_MEMORYMANAGER_H

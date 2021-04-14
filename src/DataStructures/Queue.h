//
// Created by eduardo218 on 4/5/21.
//

#ifndef C__SERVER_QUEUE_H
#define C__SERVER_QUEUE_H

#include "LinkedList.h"

template<typename T>
class Queue {
private:
    LinkedList<T> *list = new LinkedList<T>();
public:
    bool isEmpty() {
        return this->list->getLen() == 0;
    }

    void queue(T element) {
        this->list.append(element);
    }

    T peek() {
        return this->list->getHead()->getValue();
    }

    void deQueue() {
        this->list->delHead();
    }
};


#endif //C__SERVER_QUEUE_H

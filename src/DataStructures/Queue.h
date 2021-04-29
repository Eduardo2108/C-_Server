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
    /**
     * Boolean of the state of the list.
     * @return false if the list is empty, true if not empty.
     */
    bool isEmpty() {
        return this->list->getLen() == 0;
    }

    /**
     * Method for adding an element to the end of the queue
     * @param element element to queue
     */
    void queue(T element) {
        this->list->append(element);
    }

    /**
     * Method for peeking the first element on the queue
     * @return the first element on the queue.
     */
    T peek() {
        return this->list->getHead()->getValue();
    }

    /**
     * Method for deleting the first element on the queue.
     */
    void deQueue() {
        this->list->delHead();
    }

    /**
     * Method for printing the queue in the console.
     */
    void show() {
        this->list->show();

    }
};


#endif //C__SERVER_QUEUE_H

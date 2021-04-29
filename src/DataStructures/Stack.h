//
// Created by eduardo218 on 4/13/21.
//

#ifndef C__SERVER_STACK_H
#define C__SERVER_STACK_H

#include <ostream>
#include "LinkedList.h"

template<typename T>

class Stack {
private:
    LinkedList<T> list;
public:
    friend std::ostream &operator<<(std::ostream &os, const Stack &stack) {
        os << "list: " << stack.list;
        return os;
    }

public:

    /**
    * Method for printing the queue in the console.
    */
    void show() {
        this->list.show();
    }

    /**
     * Method for taking out the last element added to the top of the stack
     */
    void pop() {
        if (this->list.getLen() != 0)
            this->list.delTail();
    }

    /**
     * Method for peeking the last element added to the stack.
     * @return last element added to the stack
     */
    T peek() {
        if (this->list.getLen() != 0)
            return this->list.get(this->list.getLen() - 1);
        return nullptr;
    }

    /**
     * Method for adding a element to the top of the stack.
     * @param element
     */
    void push(T element) {
        this->list.append(element);
    }
};


#endif //C__SERVER_STACK_H

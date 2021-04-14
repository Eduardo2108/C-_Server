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
    void show(){
        this->list.show();
    }
    void pop() {
        if (this->list.getLen() != 0)
            this->list.delTail();
    }

    T peek() {
        if (this->list.getLen() != 0)
            return this->list.get(this->list.getLen() - 1);
        return nullptr;
    }

    void push(T element) {
        this->list.append(element);
    }
};


#endif //C__SERVER_STACK_H

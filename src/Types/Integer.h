//
// Created by eduardo218 on 4/5/21.
//

#ifndef C__SERVER_INTEGER_H
#define C__SERVER_INTEGER_H

#include "../Constants.h"
#include "GenericType.h"

class Integer : public GenericType{
public:
    Integer(string key, const char *value) {

        this->size = INT_SIZE;
        this->referenceCount = 0;
        this->addr = nullptr;
        this->key = key;
        this->value = value;

    }
};

#endif //C__SERVER_INTEGER_H

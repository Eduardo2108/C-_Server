//
// Created by eduardo218 on 4/5/21.
//

#ifndef C__SERVER_FLOAT_H
#define C__SERVER_FLOAT_H


#include "GenericType.h"
#include "../Constants.h"

class Float : public GenericType {
public:
    Float() {

    }

    Float(string key, const char *value) {
        this->addr = nullptr;
        this->value = value;
        this->size = FLOAT_SIZE;
        this->key = key;
        this->referenceCount = 0;
        this->value = value;

    }

};

#endif //C__SERVER_FLOAT_H

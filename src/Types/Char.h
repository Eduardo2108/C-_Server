//
// Created by eduardo218 on 4/5/21.
//

#ifndef C__SERVER_CHAR_H
#define C__SERVER_CHAR_H
#include "GenericType.h"
class Char : public GenericType {
public:
    Char( string key, const char *value) {
        this->size = CHAR_SIZE;
        this->addr = nullptr;
        this->key = key;
        this->referenceCount = 0;
        this->value = value;
    }

};

#endif //C__SERVER_CHAR_H

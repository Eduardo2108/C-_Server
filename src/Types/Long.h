//
// Created by eduardo218 on 4/5/21.
//

#ifndef C__SERVER_LONG_H
#define C__SERVER_LONG_H

class Long : public GenericType{
public:
    Long(string key, const char *value) {
        this->addr = nullptr;
        this->value = value;

        this->size = LONG_SIZE;
        this->key = key;
        this->referenceCount = 0;
    }

};

#endif //C__SERVER_LONG_H

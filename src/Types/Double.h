//
// Created by eduardo218 on 4/5/21.
//

#ifndef C__SERVER_DOUBLE_H
#define C__SERVER_DOUBLE_H

class Double : public GenericType {
public:
    Double(string key, const char *value) {
        this->size = DOUBLE_SIZE;
        this->addr = nullptr;
        this->key = key;
        this->referenceCount = 0;
        this->value = value;

    }
};

#endif //C__SERVER_DOUBLE_H

//
// Created by eduardo218 on 4/5/21.
//

#ifndef C__SERVER_GENERICTYPE_H
#define C__SERVER_GENERICTYPE_H


#include <ostream>

using namespace std;


class GenericType {
protected:
    /**Size in bytes of the variable*/
    int size;

    /**Address of where the variable its stored in the server, we get it from the server itself as a response
     * of the method "create"*/
    const char *addr;
public:
    friend ostream &operator<<(ostream &os, const GenericType &type) {
        os << "key: " << type.key << " value: " << type.value;
        return os;
    }

protected:

    /** Name of the variable, used for identifying the variable among the others, its an unique value
     * and it cannot be any of the reserved words of C!.
     */
    string key;

    /** Value stored in the variable*/
    const char *value;

    /**Reference counter on the variable*/
    int referenceCount;

public:
    int getSize() const {
        return size;
    }

    void setSize(int size) {
        GenericType::size = size;
    }

    void setAddr(const char *addr) {
        GenericType::addr = addr;
    }

    void setKey(const string &key) {
        GenericType::key = key;
    }

    bool operator==(const GenericType &rhs) const {
        return key == rhs.key;
    }

    bool operator!=(const GenericType &rhs) const {
        return !(rhs == *this);
    }

    void setValue(const char *value) {
        this->value = value;
    }

    void setReferenceCount(int referenceCount) {
        GenericType::referenceCount = referenceCount;
    }

    const char *getAddr() const {
        return this->addr;
    }

    const string &getKey() const {
        return key;
    }

    const char *getValue() const {
        return value;
    }


    int getCounter() const {
        return referenceCount;
    }

public:

    void show() {
        cout << "{ Name: " << this->key << " Value: " << this->value << " Address: " << this->addr << "}\n";
    }
};

#endif //C__SERVER_GENERICTYPE_H

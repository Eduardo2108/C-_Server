// Created by eduardo218 on 4/5/21.
//

#ifndef C__SERVER_GENERICTYPE_H
#define C__SERVER_GENERICTYPE_H


#include <ostream>
#include <string>
#include <iostream>

using namespace std;


class GenericType {
private:
    /**Size in bytes of the variable*/
    int size;
    /**Address of where the variable its stored in the server, we get it from the server itself as a response
     * of the method "create"*/
    const char *addr;
    int offset;
    string type;
public:
    const string &getType() const {
        return type;
    }

    friend ostream &operator<<(ostream &os, const GenericType &type) {
        os << "size: " << type.size << " addr: " << type.addr << " offset: " << type.offset << " type: " << type.type
           << " key: " << type.key << " value: " << type.value << " referenceCount: " << type.referenceCount;
        return os;
    }

    void setType(const string &type) {
        GenericType::type = type;
    }

public:
    int getOffset() const {
        return offset;
    }

    void setOffset(int offset) {
        GenericType::offset = offset;
    }

    int getReferenceCount() const {
        return referenceCount;
    }

public:
    private:

    /** Name of the variable, used for identifying the variable among the others, its an unique value
     * and it cannot be any of the reserved words of C!.
     */
    string key;

    /** Value stored in the variable*/
    string value;

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

        void setValue(string value) {
        this->value = value;
    }

    bool operator==(const GenericType &rhs) const {
        return key == rhs.key;
    }

    bool operator!=(const GenericType &rhs) const {
        return !(rhs == *this);
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

    string getValue() const {
        return value;
    }


    int getCounter() const {
        return referenceCount;
    }

public:

    void show() {
        cout << "{ Name: " << this->key << " Value: " << this->value << " Address: " << this->addr << " Offset: " << this->offset << "}\n";
    }
};

#endif //C__SERVER_GENERICTYPE_H

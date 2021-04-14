//
// Created by eduardo218 on 4/5/21.
//

#ifndef C__SERVER_REFERENCE_H
#define C__SERVER_REFERENCE_H

using namespace std;

class Reference {
private:
    /**Address where the object its allocated.*/
    const char *addr;
    /**Address pointed*/
    const char *pointer;
    /** Identifier for the reference type. */
    string key;

public:

    Reference() {
        ;
    }

    void setAddr(const char *addr) {
        Reference::addr = addr;
    }

    void setPointer(const char *pointer) {
        Reference::pointer = pointer;
    }

    void setKey(const string &key) {
        Reference::key = key;
    }

    const char *getAddr() const {
        return addr;
    }

    const char *const getPointer() const {
        return pointer;
    }

    void show() {
        cout << "Reference name: " << this->key << "\n"
             << "Address where its stored: " << this->addr << "\n"
             << "Address pointed: " << this->pointer << "\n";

    }

    string getKey() {
        return this->key;
    }
}
#endif //C__SERVER_REFERENCE_H

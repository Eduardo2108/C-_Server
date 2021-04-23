//
// Created by josea4718 on 4/22/21.
//
#include "ServerManager.h"

ServerManager* ServerManager::instance = nullptr;
ServerManager::ServerManager(){
    memory = new MemoryManagement(1000);
    TYPE_IDENTIFIER_LIST = new LinkedList<string>();
    TYPE_SIZES_LIST = new LinkedList<int>();

    TYPE_IDENTIFIER_LIST->append(INTEGER_KEY_WORD);
    TYPE_SIZES_LIST->append(INT_SIZE);

    TYPE_IDENTIFIER_LIST->append(FLOAT_KEY_WORD);
    TYPE_SIZES_LIST->append(FLOAT_SIZE);

    TYPE_IDENTIFIER_LIST->append(DOUBLE_KEY_WORD);
    TYPE_SIZES_LIST->append(DOUBLE_SIZE);

    TYPE_IDENTIFIER_LIST->append(CHAR_KEY_WORD);
    TYPE_SIZES_LIST->append(CHAR_SIZE);

    TYPE_IDENTIFIER_LIST->append(LONG_KEY_WORD);
    TYPE_SIZES_LIST->append(LONG_SIZE);

    TYPE_IDENTIFIER_LIST->append(REFERENCE_KEY_WORD);
    TYPE_SIZES_LIST->append(REFERENCE_SIZE);
}

ServerManager *ServerManager::getInstance() {
    if (instance == nullptr) {
        instance = new ServerManager();
    }
    return instance;
}

string ServerManager::operate(string basicString, string basicString1, string basicString2) {
    GenericType *obj1 = this->memory->getElement(basicString);
    string type = obj1->getType();
    if (type == INTEGER_KEY_WORD) {
        return this->memory->operate<int>(basicString, basicString1, basicString2);
    } else if (type == FLOAT_KEY_WORD) {
        return this->memory->operate<float>(basicString, basicString1, basicString2);

    } else if (type == DOUBLE_KEY_WORD) {
        return this->memory->operate<double>(basicString, basicString1, basicString2);

    } else if (type == CHAR_KEY_WORD) {
        return this->memory->operate<char>(basicString, basicString1, basicString2);

    } else if (type == LONG_KEY_WORD) {
        return this->memory->operate<long>(basicString, basicString1, basicString2);
    } else if (type == STRUCT_KEY_WORD) {
        cout << "Struct not implemented." << endl;
    } else if (type == REFERENCE_KEY_WORD) {
        cout << "Struct not implemented." << endl;

    }
}

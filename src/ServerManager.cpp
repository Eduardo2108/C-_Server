//
// Created by josea4718 on 4/22/21.
//
#include "ServerManager.h"

ServerManager *ServerManager::instance = nullptr;

ServerManager::ServerManager(int size) {
    memory = new MemoryManagement(size);

}

ServerManager::ServerManager() {

}

ServerManager *ServerManager::getInstance(int size) {
    if (instance == nullptr) {
        instance = new ServerManager(size);
    }
    return instance;
}

string ServerManager::operate(const string &variable_1, const string &variable_2, const string &operator_used) {
    GenericType *variable1_obj = this->memory->getElement(variable_1);
    string type = variable1_obj->getType();
    if (type == INTEGER_KEY_WORD) {
        return this->memory->operate<int>(variable_1, variable_2, operator_used);
    } else if (type == FLOAT_KEY_WORD) {
        return this->memory->operate<float>(variable_1, variable_2, operator_used);

    } else if (type == DOUBLE_KEY_WORD) {
        return this->memory->operate<double>(variable_1, variable_2, operator_used);

    } else if (type == CHAR_KEY_WORD) {
        return this->memory->operate<char>(variable_1, variable_2, operator_used);

    } else if (type == LONG_KEY_WORD) {
        return this->memory->operate<long>(variable_1, variable_2, operator_used);
    } else if (type == STRUCT_KEY_WORD) {
        cout << "Struct not implemented." << endl;
    } else if (type == REFERENCE_KEY_WORD) {
        cout << "Struct not implemented." << endl;

    }
}



//
// Created by eduardo218 on 4/20/21.
//

#ifndef C__SERVER_SERVERMANAGER_H
#define C__SERVER_SERVERMANAGER_H

#include "Util/Coms/Message.h"
#include "Util/Coms/Response.h"
#include "Constants.h"
#include "DataStructures/LinkedList.h"
#include "Types/GenericType.h"
#include "Types/Integer.h"
#include "Types/Float.h"
#include "Types/Double.h"
#include "Types/Long.h"
#include "Types/Char.h"
#include "Types/Reference.h"
#include "Util/Json.h"
#include "Memory/MemoryManagement.h"
#include "../librerias/spdlog/spdlog.h"

class ServerManager {

private:
    /**MemoryManagement.h instance, used for doing CRUD on the variables of the IDE */
    MemoryManagement *memory;

    /**Singleton instance*/
    static ServerManager *instance;

    /**Private constructor*/
    ServerManager(int size);
    ServerManager();


public:
    static ServerManager *getInstance(int size = 0);

    /**
     * Method for operating two different variables, it provides an access to the memory map, depending on the data type.
     * @param variable_1 first variable, the one whose value is going to change
     * @param variable_2  second variable, can be a variable or a name.
     * @param operator_used operation between the two elements. (=, +)
     * @return log message of the result.
     */
    void operate(const string &variable_1, const string &variable_2, const string &operator_used, Response *resp);

    /**
     * Method for processing an request from the client, converts the object from json to Message.h
     * and executes the request.
     * @param request_json json formatted instance of Message.
     * @return json formatted response object.
     */
    string processRequest(string request_json) {
        Message *request = Json::readJsonMessage(request_json);
        auto *response_generated = new Response();
        string action = request->getAction();
        if (action == CREATE) {
            //todo: caso en que la variable ya está agregada
            try {
                string json = request->getContentJson();
                int size = request->getSize();
                string type = request->getType();

                createElement(json, type, size, response_generated);
            } catch (std::bad_alloc e) {
                spdlog::error("Error creating variable.");
                response_generated->setStatusCode(INTERNAL_ERROR);
                response_generated->setMessage(e.what());
            }
        } else if (action == MODIFY) {
            try {
                string firstVar = request->getFirstVariable();
                string second = request->getSecondVariable();
                string op = request->getOperation();
                this->operate(firstVar, second, op, response_generated);
                memory->addReferenceCount(firstVar);
                memory->updateVariables();
                GenericType *obj = memory->getElement(firstVar);
                if (!obj) {
                    throw obj;
                }
                string json = Json::generateJson(obj);
                response_generated->setMessage(json);
                response_generated->setStatusCode(OK);

            } catch (GenericType e) {
                response_generated->setStatusCode(INTERNAL_ERROR);
                response_generated->setLog("Error modifying the variable.");
            }
        } else if (action == SEARCH) {
            string firstVar = request->getFirstVariable();
            try {
                memory->updateVariables();
                GenericType *obj = memory->getElement(firstVar);
                if (!obj) {
                    throw obj;
                }
                string json = Json::generateJson(obj);
                response_generated->setMessage(json);
                response_generated->setStatusCode(200);
            }
            catch (GenericType *e) {
                response_generated->setStatusCode(NOT_FOUND);
                string log = firstVar;
                log.append(ERROR_VARIABLE_NOT_FOUND);
                response_generated->setLog(log);
            }
        } else if (action == HALT) {

            this->memory->__halt();
            response_generated->setStatusCode(OK);
            response_generated->setLog("Application has stopped, all variables deleted.");

        } else if (action == COLLECTOR) {
            this->memory->__cleanMemory();
            response_generated->setStatusCode(OK);
            response_generated->setLog("Garbage collector running...");
        }
        const string &resp = Json::generateJson(response_generated);

        return resp;

    }

    string isReference(string basicString) {
        string reference;
        string type;
        for (int i = 0; i < basicString.length(); i++) {
            if (basicString[i] == '<') {
                if (!(reference == REFERENCE_KEY_WORD)) {
                    return "";
                } else {

                    for (int j = i + 1; j < basicString.length(); ++j) {
                        if (basicString[j] != '>') {
                            type.push_back(basicString[j]);
                        }
                    }
                    return type;

                }
            }
            reference.push_back(basicString[i]);
        }
    }

    GenericType *isGetAddr(string basicString) {
        string var;
        string method;
        for (int i = 0; i < basicString.length(); i++) {
            if (basicString[i] == '.') {
                for (int j = i; j < basicString.length(); ++j) {
                    method.push_back(basicString[j]);
                }
                break;
            }

            var.push_back(basicString[i]);
        }
        if (method == ".getAddr()")
            cerr << "Buscando la variable: " << var << endl;
        return this->memory->getElement(var);
    }


/**
 * Helper method for creating an variable. Provides access to the memory map, depending on the type.
 * It is separated from processRequest for simplicity.
 * @param obj_json variable to be created.
 * @param type type of the variable.
 * @param size size of the variable.
 * @param generated_response pointer to the generated_response, used for adding the information needed.
 */
    void createElement(const string &obj_json, string type, int size, Response *generated_response) {
        /**json generated from the algorithm, used to add more information, such as offset and address.*/
        string generated_json;
        /**space for storing the name of the object created.*/
        string key;

        if (type == INTEGER_KEY_WORD) {
            auto *newObject = new Integer();
            newObject = static_cast<Integer *>(Json::readJson(obj_json));
            newObject->setSize(size);
            newObject->setType(type);
            generated_json = memory->addElementDigits<int>(newObject);
            key = newObject->getKey();
        } else if (type == FLOAT_KEY_WORD) {
            auto *newObject = new Float();
            newObject = static_cast<Float *>(Json::readJson(obj_json));
            newObject->setType(type);
            newObject->setSize(size);
            generated_json = memory->addElementDigits<float>(newObject);
            key = newObject->getKey();
        } else if (type == DOUBLE_KEY_WORD) {
            auto *newObject = new Double();
            newObject = static_cast<Double *>(Json::readJson(obj_json));
            newObject->setType(type);
            newObject->setSize(size);
            generated_json = memory->addElementDigits<double>(newObject);
            key = newObject->getKey();
        } else if (type == CHAR_KEY_WORD) {
            auto *newObject = new Char();
            newObject = static_cast<Char *>(Json::readJson(obj_json));
            newObject->setType(type);
            newObject->setSize(size);
            generated_json = memory->addElementDigits<double>(newObject);
            key = newObject->getKey();
        } else if (type == LONG_KEY_WORD) {
            auto *newObject = new Long();
            newObject = static_cast<Long *>(Json::readJson(obj_json));
            newObject->setType(type);
            newObject->setSize(size);
            generated_json = memory->addElementDigits<double>(newObject);
            key = newObject->getKey();
        } else if (type == STRUCT_KEY_WORD) {
            cout << "Struct not implemented." << endl;


        } else {
            const string &reference_type = isReference(type);
            cerr << "Tipo de la referencia: " << reference_type << endl;
            if (!reference_type.empty()) {
                cout << "Reference de tipo: " << reference_type << endl;
                const string &name = Json::__readJson_name_reference(obj_json);
                const string &type = Json::__readJson_value_reference(obj_json);

                auto *newObject = new Reference();

                GenericType *pointed = isGetAddr(type);
                pointed->show();
                newObject->setType(reference_type);
                newObject->setPointer(pointed->getAddr());
                newObject->setKey(name);

                newObject->show();
                generated_json = Json::generateJson(newObject);

            }
        }
        string log = type.append(" ").append(key).append(LOG_VARIABLE_CREATED);
        generated_response->setLog(log);
        /*If the json is empty, there was an error adding the object*/
        if (generated_json.empty()) {
            generated_response->setStatusCode(INTERNAL_ERROR);
            generated_response->setLog(key.append(ERROR_NAME_OF_VARIABLE));
        } else {
            generated_response->setStatusCode(CREATED);
            generated_response->setMessage(generated_json);
        }
    }

    MemoryManagement *getMemory() const {
        return memory;
    }
};


#endif //C__SERVER_SERVERMANAGER_H

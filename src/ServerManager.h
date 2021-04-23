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
#include "MemoryManagement.h"

class ServerManager {

private:
    MemoryManagement *memory;
    LinkedList<string> *TYPE_IDENTIFIER_LIST;
    LinkedList<string> *SUPPORTED_OPERTATOR_LIST;
    LinkedList<int> *TYPE_SIZES_LIST;
    static ServerManager* instance;
    ServerManager();


public:
    static ServerManager *getInstance();

    string operate(string basicString, string basicString1, string basicString2);

    Response *processRequest(string string1) {
        Message *msg = Json::readJsonMessage(string1);
        auto *result = new Response();
        string action = msg->getAction();
        if (action == CREATE) {
            try {
                string json = msg->getContentJson();
                int size = msg->getSize();
                string type = msg->getType();
                string jsonGenerated = createElement(json, type, size);
                result->setStatusCode(OK);
                result->setMessage(jsonGenerated);
            } catch (std::bad_alloc e) {
                result->setStatusCode(INTERNAL_ERROR);
                result->setMessage(e.what());
            }
        } else if (action == MODIFY) {
            try {
                string firstVar = msg->getFirstVariable();
                string second = msg->getSecondVariable();
                string op = msg->getOperation();
                string res = this->operate(firstVar, second, op);
                result->setStatusCode(OK);
                result->setMessage(res);

            } catch (std::exception e) {

            }
        } else if (action == SEARCH) {
            string firstVar = msg->getFirstVariable();
            try {
                memory->updateVariables();
                GenericType *obj = memory->getElement(firstVar);
                if (!obj) {
                    throw obj;
                }
                string json = Json::generateJson(obj);
                result->setMessage(json);
                result->setStatusCode(200);
            }
            catch (GenericType *e) {
                result->setStatusCode(NOT_FOUND);
                result->setMessage("Variable not found");
            }

        }

        return result;
    }

    string createElement(const string &json, string type, int size) {
         string temp;
        if (type == INTEGER_KEY_WORD) {
            auto *obj = new Integer();
            obj = static_cast<Integer *>(Json::readJson(json));
            obj->setSize(size);
            obj->setType(type);
            temp = memory->addElementDigits<int>(obj);
        } else if (type == FLOAT_KEY_WORD) {
            auto *obj = new Float();
            obj = static_cast<Float *>(Json::readJson(json));
            obj->setType(type);
            obj->setSize(size);
            temp = memory->addElementDigits<float>(obj);
        } else if (type == DOUBLE_KEY_WORD) {
            auto *obj = new Double();
            obj = static_cast<Double *>(Json::readJson(json));
            obj->setType(type);
            obj->setSize(size);
            temp = memory->addElementDigits<double>(obj);
        } else if (type == CHAR_KEY_WORD) {
            auto *obj = new Char();
            obj = static_cast<Char *>(Json::readJson(json));
            obj->setType(type);
            obj->setSize(size);
            temp = memory->addElementDigits<double>(obj);
        } else if (type == LONG_KEY_WORD) {
            auto *obj = new Long();
            obj = static_cast<Long *>(Json::readJson(json));
            obj->setType(type);
            obj->setSize(size);
            temp = memory->addElementDigits<double>(obj);
        } else if (type == STRUCT_KEY_WORD) {
            cout << "Struct not implemented." << endl;
        } else if (type == REFERENCE_KEY_WORD) {
            cout << "Struct not implemented." << endl;

        }

        return temp;
    }

    MemoryManagement *getMemory() const {
        return memory;
    }
};


#endif //C__SERVER_SERVERMANAGER_H

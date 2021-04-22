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
    MemoryManagement *memory = new MemoryManagement(1000);
    LinkedList<string> *TYPE_IDENTIFIER_LIST;
    LinkedList<string> *SUPPORTED_OPERTATOR_LIST;
    LinkedList<int> *TYPE_SIZES_LIST;


public:
    Response *processRequest(Message *msg) {
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
            } catch (std::bad_alloc *e) {
                result->setStatusCode(INTERNAL_ERROR);
                result->setMessage(e->what());
            }
        }
        if (action == MODIFY) {
            try {
                string firstVar = msg->getFirstVariable();
                string second = msg->getSecondVariable();
                string op = msg->getOperation();
                //todo: get del tipo de dato de las variables para pasarlas como parametro (listas)

            } catch (std::exception e) {

            }
        }
        if (action == SEARCH) {
            string firstVar = msg->getFirstVariable();
            try {
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
        GenericType *obj;
        string temp;
        if (type == INTEGER_KEY_WORD) {
            obj = new Integer();
            obj->setType(type);
            obj = Json::readJson(json);
            obj->setSize(size);
            obj->setType(type);
            temp = memory->addElementDigits<int>(obj );
        }
        if (type == FLOAT_KEY_WORD) {
            obj = new Float();
            obj->setType(type);
            obj = Json::readJson(json);
            obj->setSize(size);
            temp = memory->addElementDigits<float>(obj);
        }
        if (type == DOUBLE_KEY_WORD) {
            obj = new Double();
            obj->setType(type);

            obj = Json::readJson(json);
            obj->setSize(size);
            temp = memory->addElementDigits<double>(obj);
        }
        if (type == CHAR_KEY_WORD) {
            obj = new Char();
            obj->setType(type);
            obj = Json::readJson(json);
            obj->setSize(size);
            temp = memory->addElementChar(obj);
        }
        if (type == LONG_KEY_WORD) {
            obj = new Long();
            obj->setType(type);
            obj = Json::readJson(json);
            obj->setSize(size);
            temp = memory->addElementDigits<long>(obj);
        }
        if (type == STRUCT_KEY_WORD) {
            cout << "Struct not implemented." << endl;
        }
        if (type == REFERENCE_KEY_WORD) {
            cout << "Struct not implemented." << endl;

        }

        return temp;
    }

    MemoryManagement *getMemory() const {
        return memory;
    }

    ServerManager() {

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


    void create(string json, int size, string type) {

    }
};


#endif //C__SERVER_SERVERMANAGER_H

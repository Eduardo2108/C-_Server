//
// Created by eduardo218 on 4/5/21.
//

#ifndef C__SERVER_JSON_H
#define C__SERVER_JSON_H


#include "../../librerias/rapidjson/stringbuffer.h"
#include "../../librerias/rapidjson/writer.h"

#include <sstream>
#include "iostream"
#include "../Types/GenericType.h"
#include "../Types/Reference.h"
#include "../../librerias/rapidjson/document.h"
#include "../Constants.h"
#include "Coms/Message.h"

using namespace rapidjson;
using namespace std;


class Json {
    //TODO: hacer singleton
public:

    static string generateJson(GenericType *obj) {
        //GET THE VALUES FROM THE OBJECT
        const char *name = obj->getKey().c_str();
        int referenceCounter = obj->getCounter();

        //CAST THE VALUE TO CONST CHAR*
        std::ostringstream valueRaw;
        valueRaw << obj->getValue();
        string var = valueRaw.str();
        const char *B = var.c_str();
        const char *value = B;

        //CAST THE ADDR TO CONST CHAR*
        std::ostringstream address;
        address << (void const *) obj->getAddr();
        string addr = address.str();
        const char *c = addr.c_str();
        const char *addr_String = c;

        //CREATE WRITER
        StringBuffer s;
        Writer <StringBuffer> writer(s);
        writer.StartObject();

        //FILL THE SPACES IN THE JSON FILE
        writer.Key(KEY_VALUE); //string name of the variable
        writer.String(name);

        writer.Key(COUNTER_VALUE);//reference referenceCount
        writer.Int(referenceCounter);

        writer.Key(ADDRESS_VALUE);//memory address
        writer.String(addr_String);

        writer.Key(VALUE_KEY);//value of the variable
        writer.Key(value);


        writer.EndObject();

        return s.GetString();

    }


    static string generateJson(Reference *obj) {
        const char *pointer = obj->getPointer();
        const char *address = obj->getAddr();
        string key = obj->getKey();



        //CREATE WRITER
        StringBuffer s;
        Writer <StringBuffer> writer(s);
        writer.StartObject();

        //IF THE REFERENCE HAS A POINTER TO A VALUE
        if (obj->getPointer() != nullptr) {
            //CAST THE POINTER TO CONST CHAR*
            std::ostringstream ptrString;
            ptrString << (void const *) pointer;
            string ptr = ptrString.str();
            const char *b = ptr.c_str();
            const char *ptr_String = b;

            writer.Key(POINTER_VALUE);
            writer.String(ptr_String);
        }
        //IF THE ADDRESS ITS ASSIGNED YET
        if (obj->getAddr() != nullptr) {
            //CAST THE ADDR TO CONST CHAR*
            std::ostringstream addrString;
            addrString << (void const *) address;
            string addr = addrString.str();
            const char *c = addr.c_str();
            const char *addr_String = c;
            writer.Key(ADDRESS_VALUE);
            writer.String(addr_String);

        }
        //FILL THE SPACES IN THE JSON FILE
        writer.Key(KEY_VALUE); //string name of the variable
        writer.String(key.c_str());


        writer.EndObject();

        return s.GetString();

    }

    static string generateJson(Message *msg) {
        //CREATE WRITER
        StringBuffer s;

        Writer<StringBuffer> writer(s);
        writer.StartObject();

        /**  "CREATE" - FOR CREATING AN INSTANCE\n
        *  "MODIFY" - FOR MODIFYING AN EXISTING INSTANCE\n
        *  "SEARCH" - FOR SEARCHING AN INSTANCE*/

        //FILL THE SPACES IN THE JSON FILE
        if (msg->getAction() == CREATE) {
            writer.Key("action");
            writer.String(CREATE);

            writer.Key("contentJson");
            writer.String(msg->getContentJson().c_str());

            writer.Key("type");
            writer.String(msg->getType().c_str());

            writer.Key("size"); //string name of the variable
            writer.Int(msg->getSize());
        }
        if (msg->getAction() == MODIFY) {
            writer.Key("action");
            writer.String(MODIFY);

            writer.Key("firstVariable");
            writer.String(msg->getFirstVariable().c_str());


            writer.Key("secondVariable"); //string name of the variable
            writer.String(msg->getSecondVariable().c_str());

            writer.Key("operator"); //string name of the variable
            writer.String(msg->getOperation().c_str());


        }
        if (msg->getAction() == SEARCH) {
            writer.Key("action");
            writer.String(SEARCH);

            writer.Key("firstVariable");
            writer.String(msg->getFirstVariable().c_str());
        }
        writer.EndObject();
        return s.GetString();

    }

    static void readJson(const string &json, GenericType *obj) {

        rapidjson::Document doc;
        doc.Parse<kParseDefaultFlags>(json.c_str());

        if (doc.HasMember(KEY_VALUE)) {
            const char *keyName = doc[KEY_VALUE].GetString();
            obj->setKey(keyName);
        }
        if (doc.HasMember(VALUE_KEY)) {
            const char *value = doc[VALUE_KEY].GetString();
            obj->setValue(value);
        }
        if (doc.HasMember(ADDRESS_VALUE)) {
            const char *addr = (doc[ADDRESS_VALUE].GetString());
            obj->setAddr(addr);
        }
        if (doc.HasMember(COUNTER_VALUE)) {
            int counter = doc[COUNTER_VALUE].GetInt();
            obj->setReferenceCount(counter);
        }
    }


    static Reference readJson(const string &json, Reference *obj) {
        rapidjson::Document doc;
        doc.Parse<kParseDefaultFlags>(json.c_str());


        if (doc.HasMember(ADDRESS_VALUE)) {
            const char *addr = (doc[ADDRESS_VALUE].GetString());
            obj->setAddr(addr);
        }
        if (doc.HasMember(POINTER_VALUE)) {
            const char *pointer = doc[POINTER_VALUE].GetString();
            obj->setPointer(pointer);
        }
        return *obj;
    }

    static Message *readJsonMessage(const string &json) {
        Message *msg = new Message();
        rapidjson::Document doc;
        doc.Parse<kParseDefaultFlags>(json.c_str());
        if (doc.HasMember(ACTION_KEY)) {
            const char *action = doc[ACTION_KEY].GetString();
            msg->setAction(action);
        }
        if (doc.HasMember(CONTENT_KEY)) {
            msg->setContentJson(doc[CONTENT_KEY].GetString());
        }
        if (doc.HasMember(SIZE_KEY)) {
            msg->setSize(doc[SIZE_KEY].GetInt());
        }
        if (doc.HasMember(TYPE_KEY)) {
            msg->setType(doc[TYPE_KEY].GetString());
        }

        if (doc.HasMember(FIRST_VAR_KEY)) {
            msg->setFirstVariable(doc[FIRST_VAR_KEY].GetString());
        }

        if (doc.HasMember(FIRST_VAR_KEY)) {
            msg->setFirstVariable(doc[FIRST_VAR_KEY].GetString());
        }
        if (doc.HasMember(SECOND_VAR_KEY)) {
            msg->setSecondVariable(doc[SECOND_VAR_KEY].GetString());
        }
        if (doc.HasMember(OPERATION_KEY)) {
            msg->setOperation(doc[OPERATION_KEY].GetString());
        }
        return msg;
    }


};

#endif //C__SERVER_JSON_H

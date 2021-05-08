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
#include "Coms/Response.h"


using namespace rapidjson;
using namespace std;


class Json {

public:
    /**
     * Converts a GenericType in Json file.
     * @param obj GenericObject instance.
     * @return string format of the json object.
     */
    static string generateJson(GenericType *obj) {
        //GET THE VALUES FROM THE OBJECT
        const char *name = obj->getKey().c_str();
        int referenceCounter = obj->getCounter();
        string addr = obj->getAddr();
        int offset = obj->getOffset();


        //CAST THE VALUE TO CONST CHAR*
        std::ostringstream valueRaw;
        valueRaw << obj->getValue();
        string var = valueRaw.str();
        const char *B = var.c_str();
        const char *value = B;

        //CREATE WRITER
        StringBuffer s;
        Writer <StringBuffer> writer(s);
        writer.StartObject();

        //FILL THE SPACES IN THE JSON FILE
        writer.Key(KEY_VALUE); //string name of the variable
        writer.String(name);


        writer.Key(ADDRESS_VALUE);//memory address
        writer.String(addr.c_str());

        writer.Key(VALUE_KEY);//value of the variable
        writer.Key(value);

        writer.Key(OFFSET_KEY);//value of the variable
        writer.Int(offset);

        writer.Key(COUNTER_VALUE);//reference referenceCount
        writer.Int(referenceCounter);

        writer.Key(OFFSET_KEY);//offset
        writer.Int(offset);


        writer.EndObject();
        string result = s.GetString();
        return s.GetString();

    }

    /**
     * Converts a Response in Json file.
     * @param obj Response instance.
     * @return string format of the json object.
     */
    static string generateJson(Response *obj) {
        //GET THE VALUES FROM THE OBJECT
        const char *msg = obj->getMessage().c_str();
        int code = obj->getStatusCode();
        const char *log = obj->getLog().c_str();
        //CREATE WRITER
        StringBuffer s;
        Writer<StringBuffer> writer(s);
        writer.StartObject();

        //FILL THE SPACES IN THE JSON FILE
        writer.Key(BODY_KEY); //string name of the variable
        writer.String(msg);

        writer.Key(LOG_KEY); //string name of the variable
        writer.String(log);

        writer.Key(CODE_KEY);//reference referenceCount
        writer.Int(code);

        writer.EndObject();

        return s.GetString();

    }

    /**
     * Converts a Reference in Json file.
     * @param obj Reference instance.
     * @return string format of the json object.
     */
    static string generateJson(Reference *obj) {
        const char *pointer = obj->getPointer();
        const char *address = obj->getAddr();
        string key = obj->getKey();



        //CREATE WRITER
        StringBuffer s;
        Writer<StringBuffer> writer(s);
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

    /**
     * Converts a Message in Json file.
     * @param obj Message instance.
     * @return string format of the json object.
     */
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


    /**
     * Reads a json object and convert it in a GenericType
     * @param json string of the object.
     * @return instance of the GenericType
     */
    static GenericType *readJson(const string &json) {
        GenericType *obj = new GenericType();
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
        if (doc.HasMember(OFFSET_KEY)) {
            int offset = doc[OFFSET_KEY].GetInt();
            obj->setOffset(offset);
        }
        if (doc.HasMember(TYPE_KEY)) {
            string type = doc[TYPE_KEY].GetString();
            obj->setType(type);
        }
        return obj;
    }

    /**
     * Reads a json object and convert it in a Reference
     * @param json string of the object.
     * @return instance of the Reference
     */
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

    static string __readJson_value_reference(string json) {
        rapidjson::Document doc;
        doc.Parse<kParseDefaultFlags>(json.c_str());

        if (doc.HasMember(VALUE_KEY)) {
            const char *value = doc[VALUE_KEY].GetString();
            cerr << "Valor leido: " << value << endl;
            return value;

        }
    }

    static string __readJson_name_reference(string json) {
        rapidjson::Document doc;
        doc.Parse<kParseDefaultFlags>(json.c_str());

        if (doc.HasMember(KEY_VALUE)) {
            const char *name = doc[KEY_VALUE].GetString();
            cerr << "Nombre leido: " << name << endl;
            return name;

        }
    }

    /**
     * Reads a json object and convert it in a Message
     * @param json string of the object.
     * @return instance of the Message
     */
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

//
// Created by eduardo218 on 4/5/21.
//

#ifndef C__SERVER_CONSTANTS_H
#define C__SERVER_CONSTANTS_H

//|---------------------------| //
//|  * SIZE OF VARIABLES *    | //
//|---------------------------| //
enum SIZE {
    INT_SIZE = 4,
    LONG_SIZE = 8,
    CHAR_SIZE = 1,
    FLOAT_SIZE = 4,
    DOUBLE_SIZE = 8,
    REFERENCE_SIZE = 4
};

//|---------------------------| //
//|    * JSON CONSTANTS  *    | //
//|---------------------------| //
static const char *const KEY_VALUE = "key";
static const char *const COUNTER_VALUE = "referenceCount";
static const char *const ADDRESS_VALUE = "addr";
static const char *const VALUE_KEY = "value";
static const char *const POINTER_VALUE = "pointer";

//For messages
static const char *const ACTION_KEY = "action";
static const char *const CONTENT_KEY = "contentJson";
static const char *const TYPE_KEY = "type";
static const char *const SIZE_KEY = "size";
static const char *const FIRST_VAR_KEY = "firstVariable";
static const char *const SECOND_VAR_KEY = "secondVariable";
static const char *const OPERATION_KEY = "operation";

//For responses
static const char *const BODY_KEY = "message";
static const char *const CODE_KEY = "statusCode";
static const int NOT_FOUND = 404;
static const int OK = 200;
static const int NOT_IMPLEMENTED = 501;
static const int INTERNAL_ERROR = 500;


//|---------------------------| //
//|   * MESSAGE CONSTANTS  *  | //
//|---------------------------| //
static const auto MODIFY = "MODIFY";
static const auto CREATE = "CREATE";
static const auto SEARCH = "SEARCH";

//|---------------------------| //
//|   * COMPILER SETTINGS  *  | //
//|---------------------------| //

//**** RESERVED WORD FOR THE LANGUAGE **** //
static const auto INTEGER_KEY_WORD = "Integer";
static const auto FLOAT_KEY_WORD = "Float";
static const auto DOUBLE_KEY_WORD = "Double";
static const auto CHAR_KEY_WORD = "Char";
static const auto LONG_KEY_WORD = "Long";
static const auto REFERENCE_KEY_WORD = "Reference";
static const auto STRUCT_KEY_WORD = "Struct";

// **** OPERATORS **** //
static const auto EQUAL_OPERATOR = "=";

// **** ERROR MESSAGES **** //
static const char *const ERROR_DATA_TYPE = " : is not a valid identifier. \n";
static const char *const ERROR_OPERATOR_ASSIGN_VALUE = "\nERROR CON EL OPERADOR A UTILIZAR\n";
static const char *const ERROR_NAME_OF_VARIABLE = "\nERROR CON EL NOMBRE DE LA VARIABLE\n";


#endif //C__SERVER_CONSTANTS_H

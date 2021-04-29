//
// Created by eduardo218 on 4/5/21.
//

#ifndef C__SERVER_CONVERTER_H
#define C__SERVER_CONVERTER_H

#include "string"

class Converter {
public:
/**
 * Converts a string into a instance of object (int, float, double, long, char)
 * @tparam T primitive data type.
 * @param var variable to convert.
 * @return converted value of the variable.
 */
    template<typename T>
    static T convertDigits(const char *var) {
        try {
            if (typeid(T) == typeid(int)) {
                return std::atoi(var);
            } else if (typeid(T) == typeid(float)) {
                return std::stof(var);
            } else if (typeid(T) == typeid(double)) {
                return std::stod(var);
            } else if (typeid(T) == typeid(long)) {
                return std::stold(var);
            }
        }
        catch (std::exception e) {
            throw e;
        }
        return 0;
    }


};


#endif //C__SERVER_CONVERTER_H

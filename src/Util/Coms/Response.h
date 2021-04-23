//
// Created by eduardo218 on 4/20/21.
//

#ifndef C__SERVER_RESPONSE_H
#define C__SERVER_RESPONSE_H

#include "string"
#include <ostream>

using namespace std;

class Response {
private:
    string message;
    int statusCode;
public:
    friend ostream &operator<<(ostream &os, const Response &response) {
        os << "message: " << response.message << " statusCode: " << response.statusCode;
        return os;
    }

    void setMessage(const string &message) {
        Response::message = message;
    }

    const string &getMessage() const {
        return message;
    }

    void show() {
        cout
                << "\n ---- Response -----\n"
                << "Status Code: " << this->statusCode << endl
                << "Message: " << this->message.c_str() << endl;

    }

    int getStatusCode() const {
        return statusCode;
    }

    void setStatusCode(int statusCode) {
        Response::statusCode = statusCode;
    }
};


#endif //C__SERVER_RESPONSE_H

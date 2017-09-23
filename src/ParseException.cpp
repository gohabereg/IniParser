#include "../headers/ParseException.h"

ParseException::ParseException(const std::string &message) {
    this->message = message;
}

const char *ParseException::what() const throw() {


    std::string message = "Error while parsing file";

    if (this->message.empty()) {
        return message.c_str();
    }

    message += ": \n\r\t" + this->message;

    return message.c_str();

}

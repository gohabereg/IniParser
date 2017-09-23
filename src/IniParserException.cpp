#include "../headers/IniParserException.h"


IniParserException::IniParserException(const std::string &message) {
    this->message = message;
}

const char *IniParserException::what() const throw() {

    std::string message = "Error while getting INI parameter";

    if (this->message.empty()) {
        return message.c_str();
    }

    message += ": \n\r\t" + this->message;

    return message.c_str();

}

#include <iostream>
#include "headers/IniParser.h"


int main() {

    IniParser parser;

    try {
        parser.load("../example.ini");
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    try {
        std::cout << parser.get<int>("DEBUG", "PlentySockMaxQSize") << std::endl;
    } catch (const IniParserException& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
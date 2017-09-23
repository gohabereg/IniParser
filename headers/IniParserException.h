#pragma once

#include <exception>
#include <string>


class IniParserException : std::exception {
public:
    IniParserException() = default;

    explicit IniParserException(const std::string &message);

    const char* what() const throw() override;

private:
    std::string message;

};


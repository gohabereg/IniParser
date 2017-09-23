#pragma once

#include <exception>
#include <string>

class ParseException : std::exception {
public:
    ParseException() = default;

    explicit ParseException(const std::string &message);

    const char* what() const throw() override;

private:
    std::string message;

};


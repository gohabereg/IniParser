#pragma once

#include <exception>
#include <string>

class FileIOException : std::exception {
public:
    FileIOException() = default;

    explicit FileIOException(const std::string &filename);

    const char* what() const throw() override;

private:
    std::string filename = "";

};



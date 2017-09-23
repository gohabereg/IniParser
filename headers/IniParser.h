#pragma once

#include <string>
#include <vector>
#include <map>
#include "FileIOException.h"
#include "ParseException.h"
#include "IniParserException.h"

class IniParser {
public:

    IniParser() = default;

    explicit IniParser(const std::string &file) throw(FileIOException, ParseException);

    ~IniParser() = default;

    void load(const std::string& file) throw(FileIOException, ParseException);

    bool hasSection(const std::string& name) const;
    bool hasParam(const std::string& section, const std::string& param) const;

    template<class T> T get(const std::string& section, const std::string& param) const throw(IniParserException);
    void print() const;

private:
    void parse() throw(ParseException);

    std::vector<std::string> input;
    std::map<std::string, std::map<std::string, std::string>> data;

};


#include "../headers/IniParser.h"
#include <iostream>
#include <fstream>
#include <regex>

/**
 * Load and parse file at once
 *
 * @param file - config filename
 */
IniParser::IniParser(const std::string &file) throw(FileIOException, ParseException) {
    this->load(file);
}

/**
 * Save file content to private field
 *
 * @param file - config file name
 */
void IniParser::load(const std::string& file) throw(FileIOException, ParseException) {

    std::ifstream ifs;
    std::string line;

    ifs.open(file, std::ifstream::in);

    if (!ifs.good()) {
        throw FileIOException(file);
    }

    /**
     * Save all lines to private field
     */
    while (ifs.good()) {
        std::getline(ifs, line);
        this->input.push_back(line);
    }

    ifs.close();

    this->parse();

};

/**
 * Clean saved content and parse it to private field
 */
void IniParser::parse() throw(ParseException){

    /**
     * Delete comments and empty lines from input file
     */
    for (int i = 0; i < this->input.size(); i++) {

        std::string line = this->input[i];

        std::size_t found = line.find(';');

        if (found != std::string::npos) {
            line.replace(found, line.length() - found, "");
        }

        found = line.find_last_not_of(' ');

        if (found != line.length() - 1) {
            line.replace(found + 1, line.length() - found + 1, "");
        }

        found = line.find_first_not_of(' ');

        if (found != 0) {
            line.replace(0, found, "");
        }

        if (line.length() == 0) {
            this->input.erase(this->input.begin() + i);
            i--;
        } else {
            this->input[i] = line;
        }

    }

    bool isFirstSectionFound = false;

    std::regex sectionRegEx("^\\[([a-zA-Z0-9_]+)\\]$");
    std::regex paramRegEx("^([a-zA-Z0-9_]+)\\s*=\\s*([a-zA-Z0-9_\\./]+)$");
    std::smatch res;
    std::string sectionName, paramName, paramValue;

    /**
     * Parse clean data to private field
     */
    for (const auto &line: this->input) {

        if (std::regex_match(line, res, sectionRegEx)) {
            sectionName = res[1];
            if (!isFirstSectionFound) {
                isFirstSectionFound = true;
            }
        } else if (std::regex_match(line, res, paramRegEx)) {

            if (!isFirstSectionFound) {
                throw ParseException("Declare parameter w\\o section");
            }

            paramName = res[1];
            paramValue = res[2];

            if (this->data.find(sectionName) == this->data.end()) {
                std::map<std::string, std::string> param;

                param.insert(std::make_pair(paramName, paramValue));
                this->data.insert(std::make_pair(sectionName, param));
            } else {
                this->data[sectionName].insert(std::make_pair(paramName, paramValue));
            }

        } else {
            throw ParseException("Invalid format in \"" + line + "\"");
        }

    }

}

/**
 * Print parsed congif in readable form
 */
void IniParser::print() const {

    for (const auto &section: this->data) {

        std::cout << "=== " << section.first << " ===" << std::endl;

        for (const auto &param: section.second) {
            std::cout << param.first << " = " << param.second << std::endl;
        }

        std::cout << std::endl;
    }

}

/**
 * Get string value by section name and param name
 *
 * @param section
 * @param param
 * @return std::string
 *
 * @throw IniParseException if section or param doesn't exist or param has invalid type
 */
template<> std::string IniParser::get<std::string>(const std::string &section, const std::string &param) const throw(IniParserException) {

    if (!this->hasSection(section)) {
        throw IniParserException("[" + section + "] section doesn't exists");
    }

    if (!this->hasParam(section, param)) {
        throw IniParserException("Parameter " + param + " in [" + section + "] section doesn't exists");
    }

    std::map<std::string, std::string> params = this->data.find(section)->second;
    std::string value = params.find(param)->second;

    return value;

}

/**
 * Get int value by section name and param name
 *
 * @param section
 * @param param
 * @return int
 *
 * @throw IniParseException if section or param doesn't exist or param has invalid type
 */
template<> int IniParser::get<int>(const std::string &section, const std::string &param) const throw(IniParserException) {

    std::string value = this->get<std::string>(section, param);

    int result;

    try {
        result = stoi(value);
    } catch (const std::invalid_argument &exc) {
        throw IniParserException("Can't convert \"" + value + "\" to int (section [" + section + "], parameter " + param + ")");
    }

    return result;

}

/**
 *
 * Get double value by section name and param name
 *
 * @param section
 * @param param
 * @return double
 *
 * @throw IniParseException if section or param doesn't exist or param has invalid type
 */
template<> double IniParser::get<double>(const std::string &section, const std::string &param) const throw(IniParserException) {

    std::string value = this->get<std::string>(section, param);

    double result;

    try {
        result = stod(value);
    } catch (const std::invalid_argument &exc) {
        throw IniParserException("Can't convert \"" + value + "\" to double (section [" + section + "], parameter " + param + ")");
    }

    return result;

}

/**
 *
 * Check if section exists
 *
 * @param name
 * @return bool
 */
bool IniParser::hasSection(const std::string &name) const {
    return (this->data.find(name) != this->data.end());
}

/**
 *
 * Check if param exists
 *
 * @param section
 * @param param
 * @return bool
 */
bool IniParser::hasParam(const std::string &section, const std::string &param) const {

    if (!this->hasSection(section)) {
        return false;
    }

    std::map<std::string, std::string> params = this->data.find(section)->second;
    return params.find(param) != params.end();

}
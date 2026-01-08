#ifndef VALIDATION_H
#define VALIDATION_H

#include <string>

class Validation {
public:
    static void validateCsvHeader(const std::string &headerLine);
    static double parseDouble(const std::string &value, const std::string &fieldName);
    static void validateNonEmpty(const std::string &value, const std::string &fieldName);
};

#endif // VALIDATION_H

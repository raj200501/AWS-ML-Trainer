#include "validation.h"
#include "utils/string_utils.h"
#include <stdexcept>

void Validation::validateCsvHeader(const std::string &headerLine) {
    const auto lower = StringUtils::toLower(headerLine);
    if (lower.find("feature") == std::string::npos || lower.find("target") == std::string::npos) {
        throw std::runtime_error("CSV header must contain 'feature' and 'target' columns. Found: " + headerLine);
    }
}

double Validation::parseDouble(const std::string &value, const std::string &fieldName) {
    const auto trimmed = StringUtils::trim(value);
    if (trimmed.empty()) {
        throw std::runtime_error("Field '" + fieldName + "' is empty");
    }
    size_t idx = 0;
    try {
        const double result = std::stod(trimmed, &idx);
        if (idx != trimmed.size()) {
            throw std::runtime_error("Field '" + fieldName + "' contains invalid characters: " + trimmed);
        }
        return result;
    } catch (const std::exception &) {
        throw std::runtime_error("Field '" + fieldName + "' is not a valid number: " + trimmed);
    }
}

void Validation::validateNonEmpty(const std::string &value, const std::string &fieldName) {
    if (StringUtils::trim(value).empty()) {
        throw std::runtime_error("Field '" + fieldName + "' must not be empty");
    }
}

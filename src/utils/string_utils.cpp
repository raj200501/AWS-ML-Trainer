#include "string_utils.h"
#include <algorithm>
#include <cctype>
#include <sstream>

std::string StringUtils::toLower(const std::string &str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    return lowerStr;
}

std::string StringUtils::trim(const std::string &str) {
    if (str.empty()) {
        return "";
    }

    auto start = str.begin();
    while (start != str.end() && std::isspace(static_cast<unsigned char>(*start))) {
        ++start;
    }
    if (start == str.end()) {
        return "";
    }

    auto end = str.end();
    do {
        --end;
    } while (end != start && std::isspace(static_cast<unsigned char>(*end)));
    return std::string(start, end + 1);
}

std::vector<std::string> StringUtils::split(const std::string &str, char delimiter) {
    std::vector<std::string> parts;
    std::stringstream stream(str);
    std::string item;
    while (std::getline(stream, item, delimiter)) {
        parts.push_back(item);
    }
    return parts;
}

bool StringUtils::startsWith(const std::string &value, const std::string &prefix) {
    return value.rfind(prefix, 0) == 0;
}

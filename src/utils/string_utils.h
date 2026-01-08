#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <string>
#include <vector>

class StringUtils {
public:
    static std::string toLower(const std::string &str);
    static std::string trim(const std::string &str);
    static std::vector<std::string> split(const std::string &str, char delimiter);
    static bool startsWith(const std::string &value, const std::string &prefix);
};

#endif // STRING_UTILS_H

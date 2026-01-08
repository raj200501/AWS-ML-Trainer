#ifndef PATH_UTILS_H
#define PATH_UTILS_H

#include <string>
#include <vector>

class PathUtils {
public:
    static std::string join(const std::string &left, const std::string &right);
    static std::string join(const std::vector<std::string> &parts);
    static std::string normalize(const std::string &path);
    static std::string baseName(const std::string &path);
};

#endif // PATH_UTILS_H

#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <string>

class FileUtils {
public:
    static bool fileExists(const std::string &filePath);
};

#endif // FILE_UTILS_H

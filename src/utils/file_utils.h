#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <string>
#include <vector>

class FileUtils {
public:
    static bool fileExists(const std::string &filePath);
    static bool directoryExists(const std::string &dirPath);
    static void createDirectory(const std::string &dirPath);
    static void createParentDirectories(const std::string &filePath);
    static std::vector<std::string> readLines(const std::string &filePath);
    static void writeLines(const std::string &filePath, const std::vector<std::string> &lines);
};

#endif // FILE_UTILS_H

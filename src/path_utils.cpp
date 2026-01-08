#include "path_utils.h"
#include <algorithm>

std::string PathUtils::join(const std::string &left, const std::string &right) {
    if (left.empty()) {
        return right;
    }
    if (right.empty()) {
        return left;
    }
    if (left.back() == '/') {
        return left + right;
    }
    return left + '/' + right;
}

std::string PathUtils::join(const std::vector<std::string> &parts) {
    std::string result;
    for (const auto &part : parts) {
        result = join(result, part);
    }
    return result;
}

std::string PathUtils::normalize(const std::string &path) {
    std::string normalized = path;
    std::replace(normalized.begin(), normalized.end(), '\\', '/');
    while (normalized.find("//") != std::string::npos) {
        normalized.erase(normalized.find("//"), 1);
    }
    return normalized;
}

std::string PathUtils::baseName(const std::string &path) {
    const std::string normalized = normalize(path);
    const auto position = normalized.find_last_of('/');
    if (position == std::string::npos) {
        return normalized;
    }
    return normalized.substr(position + 1);
}

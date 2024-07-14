#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>

class Logger {
public:
    static void init();
    static void shutdown();
    static void info(const std::string &message);
    static void warn(const std::string &message);
    static void error(const std::string &message);

private:
    static void log(const std::string &message, const std::string &level);
    static std::ofstream logFile;
};

#endif // LOGGER_H

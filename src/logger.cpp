#include "logger.h"
#include "utils/file_utils.h"
#include <chrono>
#include <ctime>
#include <iostream>

std::ofstream Logger::logFile;
std::string Logger::activeLogPath;

void Logger::init() {
    init("logs/awsmltrainer.log");
}

void Logger::init(const std::string &logFilePath) {
    activeLogPath = logFilePath;
    FileUtils::createParentDirectories(logFilePath);
    logFile.open(logFilePath, std::ios::out | std::ios::app);
    if (!logFile.is_open()) {
        std::cerr << "Failed to open log file: " << logFilePath << std::endl;
    }
}

void Logger::shutdown() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

void Logger::log(const std::string &message, const std::string &level) {
    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    if (logFile.is_open()) {
        logFile << "[" << std::ctime(&now) << "] [" << level << "] " << message << std::endl;
    }
    std::cout << "[" << level << "] " << message << std::endl;
}

void Logger::info(const std::string &message) {
    log(message, "INFO");
}

void Logger::warn(const std::string &message) {
    log(message, "WARN");
}

void Logger::error(const std::string &message) {
    log(message, "ERROR");
}

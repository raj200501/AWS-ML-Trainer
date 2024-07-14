#include "logger.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>

std::ofstream Logger::logFile;

void Logger::init() {
    logFile.open("log.txt", std::ios::out | std::ios::app);
    if (!logFile.is_open()) {
        std::cerr << "Failed to open log file." << std::endl;
    }
}

void Logger::shutdown() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

void Logger::log(const std::string &message, const std::string &level) {
    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    logFile << "[" << std::ctime(&now) << "] [" << level << "] " << message << std::endl;
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

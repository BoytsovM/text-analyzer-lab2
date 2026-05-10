#include "logger.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <sstream>

static std::ofstream log_file;
static bool use_file = false;
static LogLevel min_log_level = INFO;

static std::string get_timestamp() {
    auto now = std::time(nullptr);
    auto tm = *std::localtime(&now);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

void log_init(const std::string& filename) {
    if (!filename.empty()) {
        log_file.open(filename, std::ios::app);
        if (log_file.is_open()) {
            use_file = true;
        } else {
            std::cerr << "Cannot open log file: " << filename << std::endl;
            use_file = false;
        }
    } else {
        use_file = false;
    }
}

void log_set_level(LogLevel level) {
    min_log_level = level;
}

void log_message(LogLevel level, const std::string& message) {
    if (level < min_log_level) {
        return;
    }

    std::string prefix;
    switch (level) {
        case INFO:    prefix = "[INFO]";    break;
        case WARNING: prefix = "[WARNING]"; break;
        case ERROR:   prefix = "[ERROR]";   break;
    }

    std::string full_msg = "[" + get_timestamp() + "] " + prefix + " " + message;

    if (use_file && log_file.is_open()) {
        log_file << full_msg << std::endl;
    } else {
        std::cout << full_msg << std::endl;
    }
}

void log_close() {
    if (log_file.is_open()) {
        log_file.close();
    }
    use_file = false;
}

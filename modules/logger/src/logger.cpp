#include "logger.h"
#include <iostream>
#include <fstream>

static std::ofstream log_file;
static bool use_file = false;

void log_init(const std::string& filename) {
    if (!filename.empty()) {
        log_file.open(filename, std::ios::app);
        if (log_file.is_open()) {
            use_file = true;
        } else {
            std::cerr << "Не удалось открыть лог-файл: " << filename << std::endl;
            use_file = false;
        }
    } else {
        use_file = false;
    }
}

void log_message(LogLevel level, const std::string& message) {
    std::string prefix;
    switch (level) {
        case INFO:    prefix = "[INFO] ";    break;
        case WARNING: prefix = "[WARNING] "; break;
        case ERROR:   prefix = "[ERROR] ";   break;
    }

    std::string full_msg = prefix + message;

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

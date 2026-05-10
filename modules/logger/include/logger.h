#ifndef LOGGER_H
#define LOGGER_H

#include <string>

enum LogLevel {
    INFO,
    WARNING,
    ERROR
};

void log_init(const std::string& filename = "");
void log_message(LogLevel level, const std::string& message);
void log_set_level(LogLevel min_level);
void log_close();

#endif // LOGGER_H

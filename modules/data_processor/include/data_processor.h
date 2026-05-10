#ifndef DATA_PROCESSOR_H
#define DATA_PROCESSOR_H

#include <string>

struct ProcessResult {
    int word_count;
    int char_count;
    std::string longest_word;
};

ProcessResult process_line(const std::string& line);

#endif // DATA_PROCESSOR_H

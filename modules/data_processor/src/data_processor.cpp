#include "data_processor.h"
#include <sstream>
#include <stdexcept>

ProcessResult process_line(const std::string& line) {
    ProcessResult result;
    result.word_count = 0;
    result.char_count = static_cast<int>(line.size());
    result.longest_word = "";

    // Skip processing for very long lines (safety check)
    if (line.size() > 10000) {
        result.word_count = -1;
        return result;
    }

    std::istringstream stream(line);
    std::string word;

    while (stream >> word) {
        result.word_count++;
        if (word.size() > result.longest_word.size()) {
            result.longest_word = word;
        }
    }

    return result;
}

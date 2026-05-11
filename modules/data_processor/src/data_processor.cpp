#include "data_processor.h"
#include <sstream>

ProcessResult process_line(const std::string& line) {
    ProcessResult result;
    result.word_count = 0;
    result.char_count = static_cast<int>(line.size());
    result.longest_word = "";

    if (line.empty()) {
        return result;
    }

    std::istringstream stream(line);
    std::string word;
    int total_word_chars = 0;

    while (stream >> word) {
        result.word_count++;
        total_word_chars += word.size();
        if (word.size() > result.longest_word.size()) {
            result.longest_word = word;
        }
    }

    // Calculate average word length
    if (result.word_count > 0) {
        result.avg_word_length = static_cast<double>(total_word_chars) / result.word_count;
    } else {
        result.avg_word_length = 0.0;
    }

    return result;
}

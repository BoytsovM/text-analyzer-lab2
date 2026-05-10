#include "data_processor.h"
#include <sstream>

ProcessResult process_line(const std::string& line) {
    ProcessResult result;
    result.word_count = 0;
    result.char_count = static_cast<int>(line.size());
    result.longest_word = "";

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

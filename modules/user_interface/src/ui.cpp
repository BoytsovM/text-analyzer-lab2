#include "ui.h"
#include "data_processor.h"
#include "logger.h"
#include <fstream>
#include <string>

void run_analysis(const std::string& filepath) {
    std::ifstream file(filepath);

    if (!file.is_open()) {
        log_message(ERROR, "Failed to open file: " + filepath);
        return;
    }

    log_message(INFO, "Starting analysis of file: " + filepath);

    std::string line;
    int line_num = 0;
    int total_words = 0;

    while (std::getline(file, line)) {
        line_num++;
        ProcessResult res = process_line(line);
        total_words += res.word_count;

        std::string msg = "Line " + std::to_string(line_num) 
                          + ": words=" + std::to_string(res.word_count) 
                          + ", chars=" + std::to_string(res.char_count);

        if (!res.longest_word.empty()) {
            msg += ", longest=\"" + res.longest_word + "\"";
        }

        log_message(INFO, msg);
    }

    file.close();
    log_message(INFO, "Analysis complete. Lines: " + std::to_string(line_num) 
                + ", Total words: " + std::to_string(total_words));
}

#include "ui.h"
#include "data_processor.h"
#include "logger.h"
#include <fstream>
#include <string>

void run_analysis(const std::string& filepath) {
    std::ifstream file(filepath);

    if (!file.is_open()) {
        log_message(ERROR, "Не удалось открыть файл: " + filepath);
        return;
    }

    log_message(INFO, "Начат анализ файла: " + filepath);

    std::string line;
    int line_num = 0;

    while (std::getline(file, line)) {
        line_num++;
        ProcessResult res = process_line(line);

        std::string msg = "Строка " + std::to_string(line_num) + " обработана: слов "
                          + std::to_string(res.word_count) + ", символов "
                          + std::to_string(res.char_count);

        if (!res.longest_word.empty()) {
            msg += ", самое длинное слово: " + res.longest_word;
        }

        log_message(INFO, msg);
    }

    file.close();
    log_message(INFO, "Анализ файла завершён. Всего строк: " + std::to_string(line_num));
}

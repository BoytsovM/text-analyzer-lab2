#include "ui.h"
#include "logger.h"
#include "data_processor.h"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <cassert>

// Интеграционный тест: создаём временный файл, анализируем, проверяем лог
int main() {
    std::cout << "=== Интеграционный тест ===" << std::endl;

    // 1. Создаём временный текстовый файл
    std::string tmp_input = "test_input_tmp.txt";
    std::string tmp_log = "test_log_tmp.txt";

    {
        std::ofstream f(tmp_input);
        f << "Hello world" << std::endl;
        f << "CMake is a build system" << std::endl;
        f << "Testing" << std::endl;
    }

    // 2. Инициализируем логгер с записью в файл
    log_init(tmp_log);

    // 3. Запускаем анализ
    run_analysis(tmp_input);

    log_close();

    // 4. Проверяем, что лог-файл создан и содержит нужные записи
    std::ifstream log_check(tmp_log);
    if (!log_check.is_open()) {
        std::cerr << "FAILED: лог-файл не создан" << std::endl;
        return 1;
    }

    std::string content;
    std::string line;
    while (std::getline(log_check, line)) {
        content += line + "\n";
    }
    log_check.close();

    // Проверяем что в логе есть записи об обработке строк
    bool has_info = content.find("[INFO]") != std::string::npos;
    bool has_line1 = content.find("слов 2") != std::string::npos;  // "Hello world" - 2 слова
    bool has_line2 = content.find("слов 5") != std::string::npos;  // вторая строка - 5 слов
    bool has_finish = content.find("Всего строк: 3") != std::string::npos;

    if (has_info && has_line1 && has_line2 && has_finish) {
        std::cout << "Интеграционный тест ПРОЙДЕН" << std::endl;
    } else {
        std::cerr << "Интеграционный тест ПРОВАЛЕН" << std::endl;
        std::cerr << "Содержимое лога:" << std::endl << content << std::endl;
        remove(tmp_input.c_str());
        remove(tmp_log.c_str());
        return 1;
    }

    // 5. Тест на несуществующий файл
    log_init("");  // консольный вывод
    run_analysis("nonexistent_file_12345.txt");
    log_close();
    std::cout << "Тест ошибки открытия файла ПРОЙДЕН" << std::endl;

    // Удаляем временные файлы
    remove(tmp_input.c_str());
    remove(tmp_log.c_str());

    std::cout << "=== Все интеграционные тесты пройдены ===" << std::endl;
    return 0;
}

#include "ui.h"
#include "logger.h"
#include <iostream>
#include <string>

int main() {
    std::string log_path;
    std::cout << "Введите путь к лог-файлу (или нажмите Enter для вывода в консоль): ";
    std::getline(std::cin, log_path);

    log_init(log_path);

    std::string filepath;
    std::cout << "Введите путь к текстовому файлу для анализа: ";
    std::getline(std::cin, filepath);

    run_analysis(filepath);

    log_close();

    return 0;
}

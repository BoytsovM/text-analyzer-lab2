cmake_minimum_required(VERSION 3.14)
project(text_analyzer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Модули (статические библиотеки)
add_subdirectory(modules/data_processor)
add_subdirectory(modules/logger)
add_subdirectory(modules/user_interface)

# Основное приложение
add_subdirectory(app)

# Тесты
enable_testing()
add_subdirectory(tests)

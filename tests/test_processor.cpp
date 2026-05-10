#include "data_processor.h"
#include <iostream>
#include <cassert>
#include <string>

static int tests_passed = 0;
static int tests_failed = 0;

#define TEST(name) void name()
#define RUN_TEST(name) do { \
    std::cout << "Тест " << #name << "... "; \
    try { name(); tests_passed++; std::cout << "OK" << std::endl; } \
    catch (...) { tests_failed++; std::cout << "FAILED" << std::endl; } \
} while(0)

#define ASSERT_EQ(a, b) do { if ((a) != (b)) { \
    std::cerr << "Ожидалось " << (b) << ", получено " << (a) << std::endl; \
    throw std::runtime_error("assert failed"); } } while(0)

// Тест 1: обычная строка с несколькими словами
TEST(test_normal_line) {
    ProcessResult res = process_line("Hello world test");
    ASSERT_EQ(res.word_count, 3);
    ASSERT_EQ(res.char_count, 16);
    ASSERT_EQ(res.longest_word, std::string("Hello"));
}

// Тест 2: пустая строка
TEST(test_empty_line) {
    ProcessResult res = process_line("");
    ASSERT_EQ(res.word_count, 0);
    ASSERT_EQ(res.char_count, 0);
    ASSERT_EQ(res.longest_word, std::string(""));
}

// Тест 3: строка с одним словом
TEST(test_single_word) {
    ProcessResult res = process_line("programming");
    ASSERT_EQ(res.word_count, 1);
    ASSERT_EQ(res.char_count, 11);
    ASSERT_EQ(res.longest_word, std::string("programming"));
}

// Тест 4: строка с множественными пробелами
TEST(test_multiple_spaces) {
    ProcessResult res = process_line("  one   two  ");
    ASSERT_EQ(res.word_count, 2);
    ASSERT_EQ(res.char_count, 13);
    ASSERT_EQ(res.longest_word, std::string("one"));
}

// Тест 5: строка, где самое длинное слово - последнее
TEST(test_longest_last) {
    ProcessResult res = process_line("I am programming");
    ASSERT_EQ(res.word_count, 3);
    ASSERT_EQ(res.longest_word, std::string("programming"));
}

int main() {
    std::cout << "=== Запуск тестов для process_line ===" << std::endl;

    RUN_TEST(test_normal_line);
    RUN_TEST(test_empty_line);
    RUN_TEST(test_single_word);
    RUN_TEST(test_multiple_spaces);
    RUN_TEST(test_longest_last);

    std::cout << "===============================" << std::endl;
    std::cout << "Пройдено: " << tests_passed << ", провалено: " << tests_failed << std::endl;

    return tests_failed > 0 ? 1 : 0;
}

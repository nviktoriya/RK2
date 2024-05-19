#include <gtest/gtest.h>
#include "directory_and_file.cpp"

// Тест для вычисления размера файла
TEST(FileTest, CalculateSize) {
    File file("TestFile", 100);
    EXPECT_EQ(file.CalculateSize(), 100);
}

// Тест для добавления данных в директорию
TEST(DirectoryTest, AddData) {
    Directory dir("TestDir");
    auto file = std::make_unique<File>("TestFile", 100);
    dir.AddData(std::move(file));
    EXPECT_EQ(dir.CalculateSize(), 100);
}

// Тест для удаления данных из директории
TEST(DirectoryTest, RemoveData) {
    Directory dir("TestDir");
    auto file = std::make_unique<File>("TestFile", 100);
    auto filePtr = file.get();
    dir.AddData(std::move(file));
    dir.RemoveData(filePtr);
    EXPECT_EQ(dir.CalculateSize(), 0);
}

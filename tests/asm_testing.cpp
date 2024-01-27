#define CATCH_CONFIG_MAIN 

#include <sstream>
#include <iostream>
#include <catch2/catch.hpp>

#include "../asm/include/assembler.hpp"


TEST_CASE("Lexer constructor opens valid file", "[Lexer]") {
    REQUIRE_NOTHROW(Lexer("/home/urtoach/Desktop/proc_model/tests/testdata/valid_file.txt"));  // Replace "valid_file.asm" with an actual valid filename
}

TEST_CASE("Lexer constructor throws exception on invalid filename", "[Lexer]") {
    REQUIRE_THROWS_AS(Lexer("../testdata/invalid_file.txt"), std::invalid_argument);
}

TEST_CASE("Lexer tokenizes lines correctly", "[Lexer]") {
    Lexer lexer("/home/urtoach/Desktop/proc_model/tests/testdata/valid_file.txt");  // Replace "test_program.asm" with an actual test file
    std::cout << "---------------------------------------------------------------\n";
    for (size_t i = 0; i < lexer.lines.size(); i++) {
        std::cout << "line: " << i << "|\t";
        for (size_t j = 0; j < lexer.lines[i].size(); j++) {
            std::cout << "[" << static_cast<int>(lexer.lines[i][j].type) << ", " << lexer.lines[i][j].name << "]\t";
        }
        std::cout << std::endl;
    }
    std::cout << "---------------------------------------------------------------\n";
}


TEST_CASE("Process directory with valid input", "[processDirectory]") {
    CPUPtr cpu = std::make_shared<CPU>();

    Assemble assembler("/home/urtoach/Desktop/proc_model/tests/testdata/valid_file.txt", cpu);

    TokenLine line = {
        Token(SpecCode::LABEL, "value_name"),
        Token(SpecCode::DIRECTORY, "dd"),
        Token(SpecCode::UNKNOWN, "42"),
        Token(SpecCode::UNKNOWN, "-123")
    };

    REQUIRE_NOTHROW(assembler.processDirectory(line));

    REQUIRE(cpu->getStat() == StatCode::AOK);
    REQUIRE(cpu->ram_->initFromBinary(cpu->ram_->getData(0)) == 42);
    REQUIRE(cpu->ram_->initFromBinary(cpu->ram_->getData(1)) == -123);
}

TEST_CASE("Assembler cleaner correctly", "[Assemble]") {
    CPUPtr cpu = std::make_shared<CPU>();

    Assemble assembler("/home/urtoach/Desktop/proc_model/tests/testdata/valid_file.txt", cpu);
    assembler.cleaner();

    std::cout << "---------------------------------------------------------------\n";
    for (size_t i = 0; i < assembler.lines.size(); i++) {
        std::cout << "line: " << i << "|\t";
        for (size_t j = 0; j < assembler.lines[i].size(); j++) {
            std::cout << "[" << static_cast<int>(assembler.lines[i][j].type) << ", " << assembler.lines[i][j].name << "]\t";
        }
        std::cout << std::endl;
    }
    std::cout << "---------------------------------------------------------------\n";
}
#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>

#include "../instructions/include/operands.hpp"
#include "../instructions/include/instructions.hpp"


TEST_CASE("Operand getType", "[Operand]") {
    RegisterBlock registers;
    DataMemory memory;
    OperandPtr operand = std::make_shared<RegisterOperand>(Token(SpecCode::REGISTER, "%rax"), registers, memory);

    REQUIRE(operand->getType() == OperandType::REGISTER_OPERAND);
}

TEST_CASE("RegisterOperand getValue and setValue", "[RegisterOperand]") {
    RegisterBlock registers;
    DataMemory memory;
    RegisterOperand operand(Token(SpecCode::REGISTER, "%rax"), registers, memory);

    operand.setValue(42);
    REQUIRE(operand.getValue() == 42);
}

TEST_CASE("MemoryOperand getValue, setValue, getAddress", "[MemoryOperand]") {
    RegisterBlock registers;
    DataMemory memory;
    MemoryOperand operand(Token(SpecCode::ADDRESS, "13"), registers, memory);

    operand.setValue(123);
    REQUIRE(operand.getValue() == 123);

    REQUIRE(operand.getAddress() == 13); // Assuming default address is 0
}

TEST_CASE("ImmediateOperand getValue and setValue", "[ImmediateOperand]") {
    RegisterBlock registers;
    DataMemory memory;
    ImmediateOperand operand(Token(SpecCode::NUMBER, "-123"), registers, memory);

    operand.setValue(99);
    REQUIRE(operand.getValue() == 99);
}


TEST_CASE("Instruction creation", "[Instruction]") {
    CPU cpu;
    TokenLine tokens;
    tokens.push_back(Token(SpecCode::MNEMONIC, "1"));
    tokens.push_back(Token(SpecCode::REGISTER, "%rax"));
    tokens.push_back(Token(SpecCode::ADDRESS, "12"));
    tokens.push_back(Token(SpecCode::NUMBER, "-123"));
    tokens.push_back(Token(SpecCode::LABEL, "111"));

    SECTION("Initialization and getOperands") {
        REQUIRE_NOTHROW(Instruction(tokens, cpu));
        Instruction instr(tokens, cpu);

        auto& operands = instr.getOperands();

        REQUIRE(operands.size() == 3);
        REQUIRE(instr.getLabel() == 111);
        REQUIRE(instr.getOpcode() == 1);
    }
}
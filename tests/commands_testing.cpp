#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>

#include "../instructions/include/commands.hpp"

TEST_CASE("UnaryCommand", "[INC]") {
    CPU cpu;
    cpu.registers_->setRegister(GPRegister::rax, 3);
    cpu.ram_->setData(3, cpu.ram_->initBinary(-12));
    
    CPUPtr cpu_ptr = std::make_unique<CPU>(cpu);
    
    SECTION("REGISTER OPERAND") {
        TokenLine tokens;
        tokens.push_back(Token(SpecCode::MNEMONIC, "4"));
        tokens.push_back(Token(SpecCode::REGISTER, "%rax"));
        Instruction instruction(tokens, cpu_ptr);

        REQUIRE_NOTHROW(INC());
        INC inc;
        inc.setInstruction(instruction);
        inc.execute(cpu_ptr);

        REQUIRE(cpu_ptr->registers_->getRegister(GPRegister::rax).value == 4);
        REQUIRE(cpu_ptr->getStat() == StatCode::AOK);
    }

    SECTION("MEMORY OPERAND") {
        TokenLine tokens;
        tokens.push_back(Token(SpecCode::MNEMONIC, "4"));
        tokens.push_back(Token(SpecCode::ADDRESS, "3"));
        Instruction instruction(tokens, cpu_ptr);

        REQUIRE_NOTHROW(INC());
        INC inc;
        inc.setInstruction(instruction);
        inc.execute(cpu_ptr);

        REQUIRE(cpu_ptr->ram_->initFromBinary(cpu_ptr->ram_->getData(3)) == -11);
        REQUIRE(cpu_ptr->getStat() == StatCode::AOK);
    }
    
    SECTION("IMMEDIATE OPERAND") {
        TokenLine tokens;
        tokens.push_back(Token(SpecCode::MNEMONIC, "4"));
        tokens.push_back(Token(SpecCode::NUMBER, "-24"));
        Instruction instruction(tokens, cpu_ptr);

        REQUIRE_NOTHROW(INC());
        INC inc;
        inc.setInstruction(instruction);
        inc.execute(cpu_ptr);

        REQUIRE(cpu_ptr->getStat() == StatCode::INS);
    }
}

TEST_CASE("BinaryCommand", "[MOV]") {
    CPU cpu;
    cpu.registers_->setRegister(GPRegister::rax, 3);
    cpu.registers_->setRegister(GPRegister::rbx, -4);

    cpu.ram_->setData(3, cpu.ram_->initBinary(-12));
    cpu.ram_->setData(7, cpu.ram_->initBinary(15));
    
    CPUPtr cpu_ptr = std::make_unique<CPU>(cpu);
    
    SECTION("REGISTER OPERAND, REGISTER OPERAND") {
        TokenLine tokens;
        tokens.push_back(Token(SpecCode::MNEMONIC, "1"));
        tokens.push_back(Token(SpecCode::REGISTER, "%rax"));
        tokens.push_back(Token(SpecCode::REGISTER, "%rbx"));
        Instruction instruction(tokens, cpu_ptr);

        REQUIRE_NOTHROW(MOV());
        MOV mov;
        mov.setInstruction(instruction);
        mov.execute(cpu_ptr);

        REQUIRE(cpu_ptr->registers_->getRegister(GPRegister::rax).value == -4);
        REQUIRE(cpu_ptr->getStat() == StatCode::AOK);
    }

    SECTION("REGISTER OPERAND, MEMORY OPERAND") {
        TokenLine tokens;
        tokens.push_back(Token(SpecCode::MNEMONIC, "4"));
        tokens.push_back(Token(SpecCode::REGISTER, "%rax"));
        tokens.push_back(Token(SpecCode::ADDRESS, "3"));
        Instruction instruction(tokens, cpu_ptr);

        REQUIRE_NOTHROW(MOV());
        MOV mov;
        mov.setInstruction(instruction);
        mov.execute(cpu_ptr);

        REQUIRE(cpu_ptr->registers_->getRegister(GPRegister::rax).value == -12);
        REQUIRE(cpu_ptr->getStat() == StatCode::AOK);
    }
    
    SECTION("IMMEDIATE OPERAND, MEMORY OPERAND") {
        TokenLine tokens;
        tokens.push_back(Token(SpecCode::MNEMONIC, "4"));
        tokens.push_back(Token(SpecCode::NUMBER, "-24"));
        tokens.push_back(Token(SpecCode::ADDRESS, "7"));
        Instruction instruction(tokens, cpu_ptr);

        REQUIRE_NOTHROW(MOV());
        MOV mov;
        mov.setInstruction(instruction);
        mov.execute(cpu_ptr);

        REQUIRE(cpu_ptr->getStat() == StatCode::INS);
    }
}
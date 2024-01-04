#pragma once


#include "commands.hpp"
#include "operands.hpp"
//#include "../asm/include/assemble.hpp"

class Instruction {
private:
    uint8_t opcode;
    std::vector<OperandPtr> operands_;
public:
    Instruction(std::vector<Token> tokens);
    void execute();
};

class ProgramMemory {
private:
    std::vector<Instruction> program_;
public:
    ProgramMemory(CPU& cpu);
    void execute();
};
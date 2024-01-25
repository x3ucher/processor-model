#pragma once




#include "commands.hpp"
#include "operands.hpp"

//#include "../asm/include/assemble.hpp"

class Instruction {
private:
    size_t label;
    uint8_t opcode;
    std::vector<OperandPtr> operands_;
public:
    Instruction(const TokenLine& tokens);
    std::vector<OperandPtr> getOperands();
    size_t getLabel();
    uint8_t getOpcode() const { return opcode; }
    // void execute();
};

class ProgramMemory {
private:
    std::vector<CommandPtr> program_;
public:
    ProgramMemory();
    void pushCommand(const CommandPtr& command);
    CommandPtr getCommand(size_t address);
    void execute();
};
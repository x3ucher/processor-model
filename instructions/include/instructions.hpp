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
    Instruction(TokenLine tokens);
    void execute();
};

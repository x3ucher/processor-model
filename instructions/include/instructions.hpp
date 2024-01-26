#pragma once

#include "../../cpu/include/processor.hpp"
#include "../../asm/include/assembler.hpp"
#include "operands.hpp"

#include <memory>

class Instruction {
private:
    CPU cpu_;
    size_t label;
    uint8_t opcode;
    std::vector<OperandPtr> operands_;
public:
    Instruction(const TokenLine& tokens, CPU& cpu);
    std::vector<OperandPtr>& getOperands();
    size_t getLabel();
    uint8_t getOpcode() const { return opcode; }
    CPU& getCPU() { return cpu_; }
};

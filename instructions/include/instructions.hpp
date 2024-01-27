#pragma once

#include "../../cpu/include/processor.hpp"
//#include "../../asm/include/assembler.hpp"
#include "operands.hpp"

#include <memory>

using CPUPtr = std::shared_ptr<CPU>;

class Instruction {
private:
    CPUPtr cpu_;
    size_t label;
    uint8_t opcode;
    std::vector<OperandPtr> operands_;
public:
    Instruction(const TokenLine& tokens, CPUPtr cpu);
    std::vector<OperandPtr>& getOperands();
    size_t getLabel();
    uint8_t getOpcode() const { return opcode; }
    CPUPtr& getCPU() { return cpu_; }
};

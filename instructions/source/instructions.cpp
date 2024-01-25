#include "../include/instructions.hpp"

// Instruction
Instruction::Instruction(const TokenLine& tokens, CPU& cpu) {
    for (Token cur : tokens) {
        switch(cur.type) {
            case SpecCode::ADDRESS: {
                operands_.push_back(MemoryOperand(cur, cpu));
                break;
            }
            case SpecCode::REGISTER: {
                operands_.push_back(RegisterOperand(cur, cpu));
                break;
            }
            case SpecCode::NUMBER: {
                operands_.push_back(ImmediateOperand(cur, cpu));
                break;
            }
            case SpecCode::LABEL: {
                label = cur.name;
                break;
            }
            case SpecCode::DIRECTORY: {
                opcode = cur.name
                break;
            }
            case SpecCode::MNEMONIC: {
                opcode = cur.name:
                break;
            }
            default: {
                throw std::invalid_argument("invalid instruction");
            }
        }
    }
}
//=================================================//

// utils
std::vector<OperandPtr> Instruction::getOperands() {
    return operands_;
}

size_t Instruction::getLabel() {
    return label;
}
//================================================//

// ProgramMemory
ProgramMemory::ProgramMemory() {}

void ProgramMemory::pushCommand(const CommandPtr& command) {
    program_.push_back(command);
}

CommandPtr ProgramMemory::getCommand(size_t address) {
    return program_[address];
}
//================================================//

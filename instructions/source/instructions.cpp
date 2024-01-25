#include "../include/instructions.hpp"

// Instruction
Instruction::Instruction(const TokenLine& tokens, CPU& cpu) {
    cpu_ = cpu;
    for (Token cur : tokens) {
        switch(cur.type) {
            case SpecCode::ADDRESS: {
                operands_.push_back(std::make_shared<Operand>(MemoryOperand(cur, cpu)));
                break;
            }
            case SpecCode::REGISTER: {
                operands_.push_back(std::make_shared<Operand>(RegisterOperand(cur, cpu)));
                break;
            }
            case SpecCode::NUMBER: {
                operands_.push_back(std::make_shared<Operand>(ImmediateOperand(cur, cpu)));
                break;
            }
            case SpecCode::LABEL: {
                label = static_cast<size_t>(toInteger(cur.name));
                break;
            }
            case SpecCode::DIRECTORY: {
                opcode = static_cast<uint8_t>(toInteger(cur.name));
                break;
            }
            case SpecCode::MNEMONIC: {
                opcode = static_cast<uint8_t>(toInteger(cur.name));
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

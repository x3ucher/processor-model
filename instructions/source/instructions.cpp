#include "../include/instructions.hpp"

// Instruction
Instruction::Instruction(const TokenLine& tokens, CPUPtr cpu) : cpu_(cpu) {
    RegisterBlockPtr reg = cpu->registers_;
    DataMemoryPtr ram = cpu->ram_;

    for (auto it = tokens.begin(); it != tokens.end(); ++it) {
        //std::cout << it->name << " " << static_cast<int>(it->type) << "\n";
        switch(it->type) {
            case SpecCode::ADDRESS: {
                operands_.push_back(std::make_shared<MemoryOperand>(MemoryOperand(*it, reg, ram)));
                break;
            }
            case SpecCode::REGISTER: {
                operands_.push_back(std::make_shared<RegisterOperand>(RegisterOperand(*it, reg, ram)));
                break;
            }
            case SpecCode::NUMBER: {
                operands_.push_back(std::make_shared<ImmediateOperand>(ImmediateOperand(*it, reg, ram)));
                break;
            }
            case SpecCode::LABEL: {
                label = static_cast<size_t>(toInteger(it->name));
                break;
            }
            case SpecCode::DIRECTORY: {
                opcode = cpu->ram_->findOpcode(it->name);
                break;
            }
            case SpecCode::MNEMONIC: {
                opcode = cpu->ram_->findOpcode(it->name);
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
std::vector<OperandPtr>& Instruction::getOperands() {
    return operands_;
}

size_t Instruction::getLabel() {
    return label;
}
//================================================//



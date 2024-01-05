#include "../include/operands.hpp"

// Operand
OperandType Operand::getType() const {
    return type_;
}
//====================================================//

// RegisterOperand
RegisterOperand::RegisterOperand(const Token& token, CPU& cpu) {
    type_ = OperandType::REGISTER_OPERAND;
    processor_ = cpu;
}

int RegisterOperand::getValue() const {
    Register reg = processor_.registers_.getRegister(register_);
    return reg.value;
}

void RegisterOperand::setValue(int value) {
    processor_.registers_.setRegister(register_, value);
}
//====================================================//

// MemoryOperand
MemoryOperand::MemoryOperand(const Token& token, CPU& cpu) {
    type_ = OperandType::MEMORY_OPERAND;
    processor_ = cpu;
}

int MemoryOperand::getValue() const {
    BinData binary = processor_.ram_.getData(address_);
    int value = processor_.ram_.initFromBinary(binary);
    return value;
}

size_t MemoryOperand::getAddress() const {
    return address_;
}

void MemoryOperand::setValue(int value) {
    BinData binary = processor_.ram_.initBinary(value);
    processor_.ram_.setData(address_, binary);
}
//====================================================//

// ImmediateOperand
ImmediateOperand::ImmediateOperand(const Token& token, CPU& cpu) {
    type_ = OperandType::MEMORY_OPERAND;
    processor_ = cpu;
}

int ImmediateOperand::getValue() const {
    return value_;
}

void ImmediateOperand::setValue(int value) {
    value_ = value;
}
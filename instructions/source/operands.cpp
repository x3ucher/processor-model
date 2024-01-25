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

    if (token.name == "%rax") { register_ = GPRegister::rax; }
    else if (token.name == "%rbx") { register_ = GPRegister::rbx; }
    else if (token.name == "%rcx") { register_ = GPRegister::rcx; }
    else if (token.name == "%rdx") { register_ = GPRegister::rdx; }
    else if (token.name == "%rsp") { register_ = GPRegister::rsp; }
    else if (token.name == "%rbp") { register_ = GPRegister::rbp; }
    else if (token.name == "%rsi") { register_ = GPRegister::rsi; }
    else if (token.name == "%rdi") { register_ = GPRegister::rdi; }
    else if (token.name == "%r8") { register_ = GPRegister::r8; }
    else if (token.name == "%r9") { register_ = GPRegister::r9; }
    else if (token.name == "%r10") { register_ = GPRegister::r10; }
    else if (token.name == "%r11") { register_ = GPRegister::r11; }
    else if (token.name == "%r12") { register_ = GPRegister::r12; }
    else if (token.name == "%r13") { register_ = GPRegister::r13; }
    else if (token.name == "%r14") { register_ = GPRegister::r14; }
    else if (token.name == "%r15") { register_ = GPRegister::r15; }
    else { throw std::invalid_argument("invalid register name"); }
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
    address_ = toInteger(token.name);
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
    value_ = toInteger(token.name);
}

int ImmediateOperand::getValue() const {
    return value_;
}

void ImmediateOperand::setValue(int value) {
    value_ = value;
}
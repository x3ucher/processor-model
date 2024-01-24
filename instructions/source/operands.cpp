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
    switch(token.name) {
        case "%rax": { register_ = GPRegister::rax; break; }
        case "%rbx": { register_ = GPRegister::rbx; break; }
        case "%rcx": { register_ = GPRegister::rcx; break; }
        case "%rdx": { register_ = GPRegister::rdx; break; }
        case "%rsp": { register_ = GPRegister::rsp; break; }
        case "%rbp": { register_ = GPRegister::rbp; break; }
        case "%rsi": { register_ = GPRegister::rsi; break; }
        case "%rdi": { register_ = GPRegister::rdi; break; }
        case "%r8": { register_ = GPRegister::r8; break; }
        case "%r9": { register_ = GPRegister::r9; break; }
        case "%r10": { register_ = GPRegister::r10; break; }
        case "%r11": { register_ = GPRegister::r11; break; }
        case "%r12": { register_ = GPRegister::r12; break; }
        case "%r13": { register_ = GPRegister::r13; break; }
        case "%r14": { register_ = GPRegister::r14; break; }
        case "%r15": { register_ = GPRegister::r15; break; }
        default { throw std::invalid_argument("invalid register name"); }
    }
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
#pragma once

#include "../../cpu/include/memory.hpp"
#include "../../cpu/include/registers.hpp"
#include "../../asm/include/assembler.hpp"


class Operand {
protected:
    OperandType type_;
    RegisterBlock registers;
    DataMemory memory;
public:
    Operand(RegisterBlock& reg, DataMemory& ram) : registers(reg), memory(ram) {}
    virtual ~Operand() = default;

    OperandType getType() const;
    virtual int getValue() const = 0;
    virtual void setValue(int value) = 0;
};
//==================================================//

class RegisterOperand : public Operand {
private:
    GPRegister register_;
public:
    RegisterOperand(const Token& token, RegisterBlock& reg, DataMemory& ram);
    int getValue() const override;
    void setValue(int value) override;
};
//==================================================//

class MemoryOperand : public Operand {
private:
    size_t address_;
public:
    MemoryOperand(const Token& token, RegisterBlock& reg, DataMemory& ram);
    int getValue() const override;
    void setValue(int value) override;
    size_t getAddress() const;
};
//==================================================//

class ImmediateOperand : public Operand {
private:
    int value_;
public:
    ImmediateOperand(const Token& token, RegisterBlock& reg, DataMemory& ram);
    int getValue() const override;
    void setValue(int value) override;
};
//==================================================//

using OperandPtr = std::shared_ptr<Operand>;
//==================================================//
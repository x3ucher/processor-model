#pragma once

#include "../../utils/include/configconst.hpp"
#include "../cpu/include/processor.hpp"
#include "../../utils/include/binarycode.hpp"

using OperandPtr = std::shared_ptr<Operand>;
using CommandPtr = std::unique_ptr<Command>;
//==================================================//

class Operand {
protected:
    OperandType type_;
    CPU processor_;
public:
    virtual ~Operand() = default;

    OperandType getType() const;
    virtual int getValue() const = 0;
    virtual void setValue(int value) = 0;
};

class RegisterOperand : public Operand {
private:
    GPRegister register_;
public:
    RegisterOperand(const Token& token, CPU& cpu);
    int getValue() const override;
    void setValue(int value) override;
};

class MemoryOperand : public Operand {
private:
    size_t address_;
public:
    MemoryOperand(const Token& token, CPU& cpu);
    int getValue() const override;
    void setValue(int value) override;
    size_t getAddress() const;
};

class ImmediateOperand : public Operand {
private:
    int value_;
public:
    ImmediateOperand(const Token& token, CPU& cpu);
    int getValue() const override;
    void setValue(int value) override;
};
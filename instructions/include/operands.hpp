#pragma once

#include "configconst.hpp"

class Operand {
private:
    OperandType type_;
public:
    virtual ~Operand() = default;

    OperandType getType() const;
    virtual unsigned int getValue() const = 0;
    virtual void setValue(const unsigned int& value) = 0;
};

class RegisterOperand : public Operand {
private:
    GPRegister register_;
public:
};

class AddressOperand : public Operand {
private:
    size_t address_;
public:
};

class ImmediateOperand : public Operand {
private:
    int value_;
public:
};
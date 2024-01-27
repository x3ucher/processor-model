#pragma once

#include "../../utils/include/configconst.hpp"
#include "../../instructions/include/instructions.hpp"
#include "operands.hpp"
#include "../../cpu/include/processor.hpp"

#include <iostream>
#include <memory>

class CPU;

class Command {
public:
    virtual ~Command() = default;

    virtual void setInstruction(Instruction& instruction) = 0;
    virtual void execute(CPUPtr& processor) = 0;
};
//==================================================//

class UnaryCommand : public Command {
protected:
    OperandPtr operand;
public:
    // UnaryCommand();
    virtual ~UnaryCommand() = default;
    void setInstruction(Instruction& instruction) override;
};

class BinaryCommand : public Command {
protected:
    std::pair<OperandPtr, OperandPtr> operands;
public:
    // BinaryCommand();
    virtual ~BinaryCommand() = default;

    void setInstruction(Instruction& instruction) override;
};

class JumpCommand : public Command {
protected:
    size_t label;
public:
    // JumpCommand() : label(0) {}
    virtual ~JumpCommand() = default;

    void setInstruction(Instruction& instruction) override;
};

class DataDeclaration : public Command {
protected:
    size_t address;
    std::vector<OperandPtr> operands;
public:
    // DataDeclaration();
    virtual ~DataDeclaration() = default;
    size_t getDataAddress() { return address; }

    void setInstruction(Instruction& instruction) override;
};

class ThreadInit : public Command {
protected:
    size_t label;
public:
    // ThreadInit();
    ~ThreadInit() = default;
    void setInstruction(Instruction& instruction) override;
};

class ThreadTerminate : public Command {
protected:
public:
    // ThreadTerminate() {}
    ~ThreadTerminate() = default;
    void setInstruction(Instruction& instruction) override;
};
//==================================================//

class INC : public UnaryCommand {
public:
    // INC();
    ~INC() = default;
    void execute(CPUPtr& processor) override;
};
//==================================================//

class MOV : public BinaryCommand {
public:
    // MOV();
    ~MOV() = default;
    void execute(CPUPtr& processor) override;
};
//==================================================//

class JMP : public JumpCommand {
public:
    // JMP();
    ~JMP() = default;
    void execute(CPUPtr& processor) override;
};
//==================================================//

class DD : public DataDeclaration {
public:
    // DD();
    ~DD() = default;
    void execute(CPUPtr& processor) override;
};
//==================================================//


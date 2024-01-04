#pragma once

#include "configconst.hpp"
#include "instructions.hpp"
#include "operands.hpp"
#include "../cpu/include/processor.hpp"

#include <memory>

using OperandPtr = std::shared_ptr<Operand>;
using CommandPtr = std::unique_ptr<Command>;
//==================================================//

class Command {
private:
    StatCode stat;
    CPU processor;
public:
    Command(const Instruction& instruction, CPU& cpu);
    virtual ~Command() = 0;

    StatCode getStat() const;
    void setStat(StatCode stat);

    virtual void execute() = 0;
};
//==================================================//

class UnaryCommand : public Command {
private:
    OperandPtr operand;
public:
    UnaryCommand(const Instruction& instruction, CPU& cpu);
    virtual ~UnaryCommand();
};

class BinaryCommand : public Command {
private:
    std::pair<OperandPtr, OperandPtr> operands;
public:
    BinaryCommand(const Instruction& instruction, CPU& cpu);
    virtual ~BinaryCommand();
};

class JumpCommand : public Command {
private:
    std::string label;
public:
    JumpCommand(const Instruction& instruction, CPU& cpu);
    virtual ~JumpCommand();
};

class DataDeclaration : public Command {
private:
public:
    DataDeclaration(const Instruction& instruction, CPU& cpu);
};

class ThreadInit {
private:
public:
    ThreadInit(const Instruction& instruction, CPU& cpu);
};

class ThreadTerminate {
private:
public:
    ThreadTerminate(const Instruction& instruction, CPU& cpu);
};
//==================================================//

class INC : public UnaryCommand {
public:
    INC(const Instruction& instruction, CPU& cpu);
    void execute() override;
};
//==================================================//

class MOV : public BinaryCommand {
public:
    MOV(const Instruction& instruction, CPU& cpu);
    void execute() override;
};
//==================================================//

class JMP : public JumpCommand {
public:
    JMP(const Instruction& instruction, CPU& cpu);
    void execute() override;
};
//==================================================//

class DD : public DataDeclaration {
public:
    DD(const Instruction& instruction, CPU& cpu);
    void execute() override;
};
//==================================================//
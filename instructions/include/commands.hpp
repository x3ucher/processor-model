#pragma once

#include "../../utils/include/configconst.hpp"
#include "../../instructions/include/instructions.hpp"
#include "operands.hpp"
#include "../../cpu/include/processor.hpp"

#include <memory>

using OperandPtr = std::shared_ptr<Operand>;
using CommandPtr = std::unique_ptr<Command>;
//==================================================//

class Command {
protected:
    CPU processor;
public:
    Command(CPU& cpu) : processor(cpu) {}
    virtual ~Command() = 0;

    StatCode getStat() const;
    void setStat(StatCode stat);

    virtual void execute() = 0;
};
//==================================================//

class UnaryCommand : public Command {
protected:
    OperandPtr operand;
public:
    UnaryCommand(const Instruction& instruction, CPU& cpu);
    virtual ~UnaryCommand() = 0;
};

class BinaryCommand : public Command {
protected:
    std::pair<OperandPtr, OperandPtr> operands;
public:
    BinaryCommand(const Instruction& instruction, CPU& cpu);
    virtual ~BinaryCommand() = 0;
};

class JumpCommand : public Command {
protected:
    size_t label;
public:
    JumpCommand(const Instruction& instruction, CPU& cpu);
    virtual ~JumpCommand() = 0;
};

class DataDeclaration : public Command {
protected:
    size_t address;
    std::vector<OperandPtr> operands;
public:
    DataDeclaration(const Instruction& instruction, CPU& cpu);
    virtual ~DataDeclaration() = 0;
    size_t getDataAddress() { return address; }
};

class ThreadInit {
protected:
    size_t label;
public:
    ThreadInit(const Instruction& instruction, CPU& cpu);

};

class ThreadTerminate {
protected:
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
#pragma once

#include "../../utils/include/configconst.hpp"
#include "../../instructions/include/instructions.hpp"
#include "operands.hpp"
#include "../../cpu/include/processor.hpp"

#include <memory>

class Command {
protected:
    CPU processor;
public:
    virtual ~Command() = 0;

    StatCode getStat() const;
    void setStat(StatCode stat);

    virtual void setInstruction(Instruction& instruction);
    virtual void execute() = 0;
};
//==================================================//

class UnaryCommand : public Command {
protected:
    OperandPtr operand;
public:
    UnaryCommand();
    virtual ~UnaryCommand() = 0;

    void setInstruction(Instruction& instruction) override;
};

class BinaryCommand : public Command {
protected:
    std::pair<OperandPtr, OperandPtr> operands;
public:
    BinaryCommand();
    virtual ~BinaryCommand() = 0;

    void setInstruction(Instruction& instruction) override;
};

class JumpCommand : public Command {
protected:
    size_t label;
public:
    JumpCommand() : label(0) {}
    virtual ~JumpCommand() = 0;

    void setInstruction(Instruction& instruction) override;
};

class DataDeclaration : public Command {
protected:
    size_t address;
    std::vector<OperandPtr> operands;
public:
    DataDeclaration();
    virtual ~DataDeclaration() = 0;
    size_t getDataAddress() { return address; }

    void setInstruction(Instruction& instruction) override;
};

class ThreadInit : public Command {
protected:
    size_t label;
public:
    ThreadInit();

    void setInstruction(Instruction& instruction) override;
};

class ThreadTerminate : public Command {
protected:
public:
    ThreadTerminate() {}
    void setInstruction(Instruction& instruction) override;
};
//==================================================//

class INC : public UnaryCommand {
public:
    INC();
    void execute() override;
};
//==================================================//

class MOV : public BinaryCommand {
public:
    MOV();
    void execute() override;
};
//==================================================//

class JMP : public JumpCommand {
public:
    JMP();
    void execute() override;
};
//==================================================//

class DD : public DataDeclaration {
public:
    DD();
    void execute() override;
};
//==================================================//
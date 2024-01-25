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
    // Command(CPU& cpu) : processor(cpu) {}
    virtual ~Command() = 0;

    StatCode getStat() const;
    void setStat(StatCode stat);

    virtual void setInstruction(const Instruction& instruction);
    virtual void execute() = 0;
};
//==================================================//

class UnaryCommand : public Command {
protected:
    OperandPtr operand;
public:
    UnaryCommand() : operand(nullptr) {}
    virtual ~UnaryCommand() = 0;

    void setInstruction(const Instruction& instruction) override;
};

class BinaryCommand : public Command {
protected:
    std::pair<OperandPtr, OperandPtr> operands;
public:
    BinaryCommand() : operands(nullptr) {}
    virtual ~BinaryCommand() = 0;

    void setInstruction(const Instruction& instruction) override;
};

class JumpCommand : public Command {
protected:
    size_t label;
public:
    JumpCommand() : label(0) {}
    virtual ~JumpCommand() = 0;

    void setInstruction(const Instruction& instruction) override;
};

class DataDeclaration : public Command {
protected:
    size_t address;
    std::vector<OperandPtr> operands;
public:
    DataDeclaration() : address(0), operands(nullptr) {}
    virtual ~DataDeclaration() = 0;
    size_t getDataAddress() { return address; }

    void setInstruction(const Instruction& instruction) override;
};

class ThreadInit {
protected:
    size_t label;
public:
    ThreadInit() : label(0) {}

    void setInstruction(const Instruction& instruction) override;
};

class ThreadTerminate {
protected:
public:
    ThreadTerminate() {}
    void setInstruction(const Instruction& instruction) override;
};
//==================================================//

class INC : public UnaryCommand {
public:
    INC() : UnaryCommand() {}
    void execute() override;
};
//==================================================//

class MOV : public BinaryCommand {
public:
    MOV() : BinaryCommand() {}
    void execute() override;
};
//==================================================//

class JMP : public JumpCommand {
public:
    JMP() : JumpCommand() {}
    void execute() override;
};
//==================================================//

class DD : public DataDeclaration {
public:
    DD() : DataDeclaration() {}
    void execute() override;
};
//==================================================//
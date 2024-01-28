#pragma once

#include "../../utils/include/configconst.hpp"
#include "../../instructions/include/instructions.hpp"
#include "operands.hpp"
#include "../../cpu/include/processor.hpp"

#include <iostream>
#include <memory>

// class CPU;

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

class HLT : public Command {
public:
    ~HLT() = default;
    void setInstruction(Instruction& instruction) override;
    void execute(CPUPtr& processor) override;
};

/*
class ThreadInit : public Command {
protected:
    size_t label;
public:
    // ThreadInit();
    ~ThreadInit() = default;
    void setInstruction(Instruction& instruction) override;
    void execute(CPUPtr& processor) override;
};

class ThreadTerminate : public Command {
protected:
public:
    // ThreadTerminate() {}
    ~ThreadTerminate() = default;
    void setInstruction(Instruction& instruction) override;
    void execute(CPUPtr& processor) override;
};
*/
//==================================================//

class INC : public UnaryCommand {
public:
    // INC();
    ~INC() = default;
    void execute(CPUPtr& processor) override;
};

class DEC : public UnaryCommand {
public:
    ~DEC() = default;
    void execute(CPUPtr& processor) override;
};

class NOT : public UnaryCommand {
public:
    ~NOT() = default;
    void execute(CPUPtr& processor) override;
};
//==================================================//

class MOV : public BinaryCommand {
public:
    ~MOV() = default;
    void execute(CPUPtr& processor) override;
};

class ADD : public BinaryCommand {
public:
    ~ADD() = default;
    void execute(CPUPtr& processor) override;
};

class SUB : public BinaryCommand {
public:
    ~SUB() = default;
    void execute(CPUPtr& processor) override;
};

class AND : public BinaryCommand {
public:
    ~AND() = default;
    void execute(CPUPtr& processor) override;
};

class OR : public BinaryCommand {
public:
    ~OR() = default;
    void execute(CPUPtr& processor) override;
};

class XOR : public BinaryCommand {
public:
    ~XOR() = default;
    void execute(CPUPtr& processor) override;
};

class CMP : public BinaryCommand {
public:
    ~CMP() = default;
    void execute(CPUPtr& processor) override;
};

class SHL : public BinaryCommand {
public:
    ~SHL() = default;
    void execute(CPUPtr& processor) override;
};

class SHR : public BinaryCommand {
public:
    ~SHR() = default;
    void execute(CPUPtr& processor) override;
};
//==================================================//

class JMP : public JumpCommand {
public:
    // JMP();
    ~JMP() = default;
    void execute(CPUPtr& processor) override;
};

class JE : public JumpCommand {
public:
    ~JE() = default;
    void execute(CPUPtr& processor) override;
};

class JNE : public JumpCommand {
public:
    ~JNE() = default;
    void execute(CPUPtr& processor) override;
};

class JG : public JumpCommand {
public:
    ~JG() = default;
    void execute(CPUPtr& processor) override;
};

class JGE : public JumpCommand {
public:
    ~JGE() = default;
    void execute(CPUPtr& processor) override;
};

class JL : public JumpCommand {
public:
    ~JL() = default;
    void execute(CPUPtr& processor) override;
};

class JLE : public JumpCommand {
public:
    ~JLE() = default;
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


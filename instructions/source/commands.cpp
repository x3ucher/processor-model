#include "../include/commands.hpp"

// Command
StatCode Command::getStat() const {
    return processor.stat_;
}
//=================================================//
// UnaryCommand
/* UnaryCommand::UnaryCommand(const Instruction& instruction) {
    operand = (instruction.getOperands())[0];
}*/
void UnaryCommand::setInstruction(const Instruction& instr) override {
    operand = (instr.getOperands())[0];
}

// BinaryCommand
/* BinaryCommand::BinaryCommand(const Instruction& instruction) {
    operands = { (instruction.getOperands())[0], (instruction.getOperands())[1] };
}*/
void BinaryCommand::setInstruction(const Instruction& instr) override {
    operands = { (instr.getOperands())[0], (instr.getOperands())[1] };
}

// JumpCommand
/* JumpCommand::JumpCommand(const Instruction& instruction) {
    label = instruction.getLabel();
}*/
void JumpCommand::setInstruction(const Instruction& instr) override {
    label = instr.getLabel();
}

// DataDeclaration
/* DataDeclaration::DataDeclaration(const Instruction& instruction) {
    operands = instruction.getOperands();
}*/
void DataDeclaration::setInstruction(const Instruction& instr) override {
    operands = instr.getOperands();
}

// ThreadInit
/* ThreadInit::ThreadInit(const Instruction& instruction) {
    label = instruction.getLabel();
}*/
void ThreadInit::setInstruction(const Instruction& instr) override {
    label = instr.getLabel();
}

// ThreadTerminate
/* ThreadTerminate::ThreadTerminate(const Instruction& instruction) {}*/
//=================================================//

// Unary
// INC
INC::INC(const Instruction& instruction) : UnaryCommand(instruction) {}

void INC::execute(){
    if (UnaryCommand::getOperand()) {
        operand_->setValue(operand_->getValue() + 1);
        processor.setStat(StatCode::AOK);
    }
    else {
        processor.setStat(StatCode::INS);
    }
}
//=================================================//

// Binary
// MOV
MOV::MOV(const Instruction& instruction) : BinaryCommand(instruction) {}

void MOV::execute() {
    if (operands->first.getType() == OperandType::IMMEDIATE_OPERAND){
        processor.setStat(StatCode::INS);
    }
    else {
        (operands->first).setValue((operands->second).getValue);
        processor.setStat(StatCode::AOK);
    }
}
//=================================================//

// Jumps
// JMP
JMP::JMP(const Instruction& instruction) : JumpCommand(instruction) {}

void JMP::execute() {
    try {
        processor.setPC(label - 1);
        processor.setStat(StatCode::AOK);
    }
    catch(...) { processor.setStat(StatCode::INS); }
}
//=================================================//

// DataDeclaration
// DD
DD::DD(const Instruction& instruction) : DataDeclaration(instruction) {}

void DD::execute() {
    try {
        address = processor.ram_.getLastAddress(); 
        for (size_t i = 0; i < instruction.operands_.size(); i++) {
            BinData bin = processor.ram_.initBinary(instruction.operands_[i].type, instruction.operands_[i].name);
            processor.ram_.setData(bin);
        }
    }
    catch(...) { processor.setStat(StatCode::INS); }
}
//=================================================//
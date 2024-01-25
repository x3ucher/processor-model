#include "../include/commands.hpp"

// Command
StatCode Command::getStat() const {
    return processor.getStat();
}
//=================================================//
// UnaryCommand
/* UnaryCommand::UnaryCommand(const Instruction& instruction) {
    operand = (instruction.getOperands())[0];
}*/
void UnaryCommand::setInstruction(Instruction& instr) {
    processor = instr.getCPU();
    operand = (instr.getOperands())[0];
}

// BinaryCommand
/* BinaryCommand::BinaryCommand(const Instruction& instruction) {
    operands = { (instruction.getOperands())[0], (instruction.getOperands())[1] };
}*/
void BinaryCommand::setInstruction(Instruction& instr) {
    processor = instr.getCPU();
    operands = std::make_pair((instr.getOperands())[0], (instr.getOperands())[1]);
}

// JumpCommand
/* JumpCommand::JumpCommand(const Instruction& instruction) {
    label = instruction.getLabel();
}*/
void JumpCommand::setInstruction(Instruction& instr) {
    processor = instr.getCPU();
    label = instr.getLabel();
}

// DataDeclaration
/* DataDeclaration::DataDeclaration(const Instruction& instruction) {
    operands = instruction.getOperands();
}*/
void DataDeclaration::setInstruction(Instruction& instr) {
    processor = instr.getCPU();
    operands = instr.getOperands();
}

// ThreadInit
/* ThreadInit::ThreadInit(const Instruction& instruction) {
    label = instruction.getLabel();
}*/
void ThreadInit::setInstruction(Instruction& instr) {
    processor = instr.getCPU();
    label = instr.getLabel();
}

// ThreadTerminate
/* ThreadTerminate::ThreadTerminate(const Instruction& instruction) {}*/
//=================================================//

// Unary
// INC
//INC::INC(Instruction& instruction) : UnaryCommand(instruction) {}

void INC::execute(){
    if (operand) {
        operand->setValue(operand->getValue() + 1);
        processor.setStat(StatCode::AOK);
    }
    else {
        processor.setStat(StatCode::INS);
    }
}
//=================================================//

// Binary
// MOV
//MOV::MOV(const Instruction& instruction) : BinaryCommand(instruction) {}

void MOV::execute() {
    if (operands.first->getType() == OperandType::IMMEDIATE_OPERAND){
        processor.setStat(StatCode::INS);
    }
    else {
        operands.first->setValue(operands.second->getValue);
        processor.setStat(StatCode::AOK);
    }
}
//=================================================//

// Jumps
// JMP
//JMP::JMP(const Instruction& instruction) : JumpCommand(instruction) {}

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
//DD::DD(const Instruction& instruction) : DataDeclaration(instruction) {}

void DD::execute() {
    try {
        address = processor.ram_.getLastAddress(); 
        for (size_t i = 0; i < operands.size(); i++) {
            BinData bin = processor.ram_.initBinary(operands[i].type, operands[i].name);
            processor.ram_.setData(bin);
        }
    }
    catch(...) { processor.setStat(StatCode::INS); }
}
//=================================================//
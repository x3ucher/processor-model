#include "../include/commands.hpp"


// UnaryCommand
void UnaryCommand::setInstruction(Instruction& instr) {
    operand = (instr.getOperands())[0];
}

// BinaryCommand
void BinaryCommand::setInstruction(Instruction& instr) {
    // processor = instr.getCPU();
    operands = std::make_pair((instr.getOperands())[0], (instr.getOperands())[1]);
}

// JumpCommand
void JumpCommand::setInstruction(Instruction& instr) {
    // processor = instr.getCPU();
    label = instr.getLabel();
}

// DataDeclaration
void DataDeclaration::setInstruction(Instruction& instr) {
    // processor = instr.getCPU();
    operands = std::move(instr.getOperands());
}

// ThreadInit
/*
void ThreadInit::setInstruction(Instruction& instr) {
    // processor = instr.getCPU();
    label = instr.getLabel();
}
*/

// ThreadTerminate
//=================================================//

// HLT
void HLT::setInstruction(Instruction& instr) {}

void HLT::execute(CPUPtr& processor) {
    processor->setStat(StatCode::HLT);
}
//=================================================//

// Unary
// INC
void INC::execute(CPUPtr& processor){
    if (operand->getType() != OperandType::IMMEDIATE_OPERAND) {
        operand->setValue(operand->getValue() + 1);
        processor->setStat(StatCode::AOK);
    }
    else {
        processor->setStat(StatCode::INS);
    }
}
//=================================================//

// Binary
// MOV
void MOV::execute(CPUPtr& processor) {
    if (operands.first->getType() == OperandType::IMMEDIATE_OPERAND){
        processor->setStat(StatCode::INS);
    }
    else {
        operands.first->setValue(operands.second->getValue());
        processor->setStat(StatCode::AOK);
    }
}
//=================================================//

// Jumps
// JMP
void JMP::execute(CPUPtr& processor) {
    try {
        processor->setPC(label - 1);
        processor->setStat(StatCode::AOK);
    }
    catch(...) { processor->setStat(StatCode::INS); }
}
//=================================================//

// DataDeclaration
// DD
void DD::execute(CPUPtr& processor) {
    try {
        address = processor->ram_->getDataSize(); 
        for (size_t i = 0; i < operands.size(); i++) {
            BinData bin = processor->ram_->initBinary(operands[i]->getValue());
            processor->ram_->setData(bin);
        }
        processor->setStat(StatCode::AOK);
    }
    catch(...) { processor->setStat(StatCode::INS); }
}
//=================================================//
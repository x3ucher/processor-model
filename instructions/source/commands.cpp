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

// DEC
void DEC::execute(CPUPtr& processor) {
    if (operand->getType() != OperandType::IMMEDIATE_OPERAND) {
        operand->setValue(operand->getValue() - 1);
        processor->setStat(StatCode::AOK);
    }
    else {
        processor->setStat(StatCode::INS);
    }
}

// NOT
void NOT::execute(CPUPtr& processor) {
    if (operand->getType() != OperandType::IMMEDIATE_OPERAND) {
        operand->setValue(~(operand->getValue()));
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

// ADD
void ADD::execute(CPUPtr& processor) {
    if (operands.first->getType() == OperandType::IMMEDIATE_OPERAND){
        processor->setStat(StatCode::INS);
    }
    else {
        OperandPtr op1 = operands.first;
        OperandPtr op2 = operands.second; 
        op1->setValue(op1->getValue() + op2->getValue());
        processor->setStat(StatCode::AOK);
    }
}

// SUB
void SUB::execute(CPUPtr& processor) {
    if (operands.first->getType() == OperandType::IMMEDIATE_OPERAND){
        processor->setStat(StatCode::INS);
    }
    else {
        OperandPtr op1 = operands.first;
        OperandPtr op2 = operands.second; 
        op1->setValue(op1->getValue() - op2->getValue());
        processor->setStat(StatCode::AOK);
    }
}

// AND
void AND::execute(CPUPtr& processor) {
    if (operands.first->getType() == OperandType::IMMEDIATE_OPERAND){
        processor->setStat(StatCode::INS);
    }
    else {
        OperandPtr op1 = operands.first;
        OperandPtr op2 = operands.second; 
        op1->setValue(op1->getValue() & op2->getValue());
        if (op1->getValue() == 0) { processor->flags_[static_cast<size_t>(ConditionFlags::ZF)] = true; }
        else { processor->flags_[static_cast<size_t>(ConditionFlags::ZF)] = false; }
        processor->setStat(StatCode::AOK);
    }
}

// OR
void OR::execute(CPUPtr& processor) {
    if (operands.first->getType() == OperandType::IMMEDIATE_OPERAND){
        processor->setStat(StatCode::INS);
    }
    else {
        OperandPtr op1 = operands.first;
        OperandPtr op2 = operands.second; 
        op1->setValue(op1->getValue() | op2->getValue());
        if (op1->getValue() == 0) { processor->flags_[static_cast<size_t>(ConditionFlags::ZF)] = true; }
        else { processor->flags_[static_cast<size_t>(ConditionFlags::ZF)] = false; }
        processor->setStat(StatCode::AOK);
    }
}

void XOR::execute(CPUPtr& processor) {
    if (operands.first->getType() == OperandType::IMMEDIATE_OPERAND){
        processor->setStat(StatCode::INS);
    }
    else {
        int op1 = operands.first->getValue();
        int op2 = operands.second->getValue(); 
        operands.first->setValue((~op1 & op2) | (~op2 & op1));
        if (operands.first->getValue() == 0) { processor->flags_[static_cast<size_t>(ConditionFlags::ZF)] = true; }
        else { processor->flags_[static_cast<size_t>(ConditionFlags::ZF)] = false; }
        processor->setStat(StatCode::AOK);
    }
}

void CMP::execute(CPUPtr& processor) {
    try{
        if (operands.first->getValue() == operands.second->getValue()) {
            processor->flags_[static_cast<size_t>(ConditionFlags::ZF)] = true;
            processor->flags_[static_cast<size_t>(ConditionFlags::CF)] = false;
            processor->flags_[static_cast<size_t>(ConditionFlags::OF)] = false;
        }
        else {
            processor->flags_[static_cast<size_t>(ConditionFlags::ZF)] = true;
            processor->flags_[static_cast<size_t>(ConditionFlags::CF)] = operands.first->getValue() < operands.second->getValue(); 
            processor->flags_[static_cast<size_t>(ConditionFlags::OF)] = false;
        }
        processor->setStat(StatCode::AOK);
    }
    catch(...){
        processor->setStat(StatCode::INS);
    }
}

// SHL
void SHL::execute(CPUPtr& processor) {
    if (operands.second->getValue() <= 0) {
        processor->setStat(StatCode::INS);
    } 
    else {
        operands.first->setValue(operands.first->getValue() << operands.second->getValue());
        processor->setStat(StatCode::AOK);
    }
}

// SHR
void SHR::execute(CPUPtr& processor) {
    if (operands.second->getValue() <= 0) {
        processor->setStat(StatCode::INS);
    } 
    else {
        operands.first->setValue(operands.first->getValue() >> operands.second->getValue());
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

// JE
void JE::execute(CPUPtr& processor) {
    try {
        if (processor->flags_[static_cast<size_t>(ConditionFlags::ZF)]) {
            processor->setPC(label - 1);
        }
        processor->setStat(StatCode::AOK);
    }
    catch(...) { processor->setStat(StatCode::INS); }
}

// JNE
void JNE::execute(CPUPtr& processor) {
    try {
        if (!processor->flags_[static_cast<size_t>(ConditionFlags::ZF)]) {
            processor->setPC(label - 1);
        }
        processor->setStat(StatCode::AOK);
    }
    catch(...) { processor->setStat(StatCode::INS); }
}

// JG
void JG::execute(CPUPtr& processor) {
    try {
        if (!(processor->flags_[static_cast<size_t>(ConditionFlags::SF)] ^ processor->flags_[static_cast<size_t>(ConditionFlags::OF)]) & !processor->flags_[static_cast<size_t>(ConditionFlags::ZF)]) {
            processor->setPC(label - 1);
        }
        processor->setStat(StatCode::AOK);
    }
    catch(...) { processor->setStat(StatCode::INS); }
}

// JGE
void JGE::execute(CPUPtr& processor) {
    try {
        if (!processor->flags_[static_cast<size_t>(ConditionFlags::SF)] ^ processor->flags_[static_cast<size_t>(ConditionFlags::OF)]) {
            processor->setPC(label - 1);
        }
        processor->setStat(StatCode::AOK);
    }
    catch(...) { processor->setStat(StatCode::INS); }
}

// JL
void JL::execute(CPUPtr& processor) {
    try {
        if (processor->flags_[static_cast<size_t>(ConditionFlags::SF)] ^ processor->flags_[static_cast<size_t>(ConditionFlags::OF)]) {
            processor->setPC(label - 1);
        }
        processor->setStat(StatCode::AOK);
    }
    catch(...) { processor->setStat(StatCode::INS); }
}

// JLE
void JLE::execute(CPUPtr& processor) {
    try {
        if ((processor->flags_[static_cast<size_t>(ConditionFlags::SF)] ^ processor->flags_[static_cast<size_t>(ConditionFlags::OF)]) | processor->flags_[static_cast<size_t>(ConditionFlags::ZF)]) {
            processor->setPC(label - 1);
        }
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
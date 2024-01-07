 #include "../include/commands.hpp"

 // Command
StatCode Command::getStat() const {
    return processor.stat_;
}
//=================================================//

// UnaryCommand
UnaryCommand::UnaryCommand(const Instruction& instruction, CPU& cpu) : Command(cpu) {
    operand = (instruction.getOperands())[0];
}

// BinaryCommand
BinaryCommand::BinaryCommand(const Instruction& instruction, CPU& cpu) : Command(cpu) {
    operands = { (instruction.getOperands())[0], (instruction.getOperands())[1] };
}

// JumpCommand
JumpCommand::JumpCommand(const Instruction& instruction, CPU& cpu) : Command(cpu) {
    label = instruction.getLabel();
}

// DataDeclaration
DataDeclaration::DataDeclaration(const Instruction& instruction, CPU& cpu) : Command(cpu), address(0) {
    operands = instruction.getOperands();
}

// ThreadInit
ThreadInit::ThreadInit(const Instruction& instruction, CPU& cpu) : Command(cpu) {
    label = instruction.getLabel();
}

// ThreadTerminate
ThreadTerminate::ThreadTerminate(const Instruction& instruction, CPU& cpu) : Command(cpu) {}
//=================================================//

// Unary
// INC
INC::INC(const Instruction& instruction, CPU& cpu) : UnaryCommand(instruction, cpu) {}

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
MOV::MOV(const Instruction& instruction, CPU& cpu) : BinaryCommand(instruction, cpu) {}

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
JMP::JMP(const Instruction& instruction, CPU& cpu) : JumpCommand(instruction, cpu) {}

void JMPFunc::execute() {
    try {
        processor.setPC(label - 1);
        processor.setStat(StatCode::AOK);
    }
    catch(...) { processor.setStat(StatCode::INS); }
}


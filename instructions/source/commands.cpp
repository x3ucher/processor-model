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

// INC
INC::INC(const Instruction& instruction, CPU& cpu) : UnaryCommand(instruction, cpu) {}

void INC::execute(){
    if (UnaryCommand::getOperand()) {
        operand_->setValue(operand_->getValue() + 1);
        (StatCode::AOK);
    }
    else {
        setStat(StatCode::INS);
    }
}
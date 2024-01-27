#include "../include/processor.hpp"

//CPU
StatCode CPU::getStat() const { 
    return stat_;
}

void CPU::setStat(StatCode stat) {
    stat_ = stat;
}

size_t CPU::getPC() const {
    return static_cast<size_t>((registers_->getRegister(GPRegister::r15)).value);
}

void CPU::setPC(size_t address) {
    registers_->setRegister(GPRegister::r15, static_cast<int>(address));
}

//void CPU::execute() {
//    program_.execute(std::make_shared<CPU>(this));
//}
//=============================================//

// ProgramMemory
ProgramMemory::ProgramMemory() {
    program_.resize(0);
}

void ProgramMemory::pushCommand(const CommandPtr& command) {
    program_.push_back(command);
}

CommandPtr ProgramMemory::getCommand(size_t address) {
    return program_[address];
}


//=================================================//
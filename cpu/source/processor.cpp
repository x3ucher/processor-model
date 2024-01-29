//#include "../include/processor.hpp"
#include "../../instructions/include/commands.hpp"
#include "../../asm/include/assembler.hpp"

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

void CPU::execute() {
    CPUPtr ptr = std::make_shared<CPU>(*this);
    program_.execute(ptr);
    if (getStat() == StatCode::ADR) {
        throw std::runtime_error("invalid address");
    }
    else if (getStat() == StatCode::INS) {
        throw std::runtime_error("invalid address");
    }
}

void CPU::loadProgram(ProgramMemory& program) {
    //CPUPtr ptr = std::make_shared<CPU>(*this); 
    //Assemble ass(filename, ptr);
    program_ = program;
}

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

void ProgramMemory::execute(CPUPtr& cpu) {
    while(cpu->getStat() == StatCode::AOK) {
        size_t pc = cpu->getPC();
        (program_[pc])->execute(cpu);
        cpu->setPC(cpu->getPC() + 1);

        cpu->ram_->print();
        cpu->registers_->print();
    }
}
//=================================================//
#pragma once

#include "../../utils/include/configconst.hpp"
#include "../../cpu/include/registers.hpp"
#include "../../cpu/include/thread.hpp"
#include "../../cpu/include/memory.hpp"
#include "../../instructions/include/commands.hpp"

class CPU {
private:
    StatCode stat_;
public:
    std::array<bool, NUMBER_OF_FLAGS> flags_;
    RegisterBlock registers_;
    // std::vector<Thread> threads_;
    DataMemory ram_;
    ProgramMemory program_; 

    // methods
    CPU::CPU() : stat_(StatCode::AOK), flags_({}), registers_(), ram_(), program_() {}

    // getters
    StatCode getStat() const;
    size_t getPC() const;

    // setters
    void setStat(StatCode stat);
    void setPC(size_t address);

    void execute();
};
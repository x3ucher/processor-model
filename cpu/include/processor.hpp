#pragma once

#include "../utils/include/configconst.hpp"
#include "include/registers.hpp"
#include "include/thread.hpp"
#include "include/memory.hpp"

class CPU {
public:
    StatCode stat_;
    std::array<bool, NUMBER_OF_FLAGS> flags_;
    RegisterBlock registers_;
    // std::vector<Thread> threads_;
    DataMemory ram_;
    ProgramMemory program_; 

    // methods
    CPU();

    // getters
    StatCode getStat() const;
    size_t getPC() const;

    // setters
    void setStat(StatCode stat);
    void setPC(size_t address);

    void execute();
};
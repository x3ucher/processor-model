#pragma once

#include "../utils/include/configconst.hpp"
#include "include/registers.hpp"
#include "include/thread.hpp"
#include "include/memory.hpp"

class CPU {
private:
    StatCode stat_;
    std::array<bool, NUMBER_OF_FLAGS> flags_;
    RegisterBlock registers_;
    std::vector<Thread> threads_;
    RAM ram_;
    ProgramMemory program_;
public:
    CPU();

    void execute();
};
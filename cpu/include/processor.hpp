#pragma once

#include "../../utils/include/binarycode.hpp"
#include "../../cpu/include/registers.hpp"
// #include "../../cpu/include/thread.hpp"
#include "../../cpu/include/memory.hpp"
//#include "../../asm/include/assembler.hpp"
// #include "../../instructions/include/commands.hpp"

using Flags = std::array<bool, NUMBER_OF_FLAGS>;
using FlagsPtr = std::shared_ptr<Flags>;

class Command;
class CPU;

using CommandPtr = std::shared_ptr<Command>;
using CPUPtr = std::shared_ptr<CPU>;

class ProgramMemory {
private:
    std::vector<CommandPtr> program_;
public:
    ProgramMemory();
    void pushCommand(const CommandPtr& command);
    CommandPtr getCommand(size_t address);
    void execute(CPUPtr& cpu);
};

//==================================================//

class CPU {
public:
    StatCode stat_;
    Flags flags_;
    RegisterBlockPtr registers_;
    DataMemoryPtr ram_;
    ProgramMemory program_; 

    // methods
    //CPU() : stat_(StatCode::AOK), flags_({}), registers_(), ram_(), program_() {}
    CPU() : stat_(StatCode::AOK),
            flags_({}),
            registers_(std::make_shared<RegisterBlock>()),
            ram_(std::make_shared<DataMemory>()),
            program_() {}

    // getters
    StatCode getStat() const;
    size_t getPC() const;

    // setters
    void setStat(StatCode stat);
    void setPC(size_t address);

    void loadProgram(ProgramMemory& program);
    void execute();
};
//==================================================//

using CommandPtr = std::shared_ptr<Command>;
//==================================================//


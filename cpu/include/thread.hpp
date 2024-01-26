#pragma once

#include <thread>
#include <string>
#include <mutex>
#include <functional>

#include "include/registers.hpp"

using Flags = std::array<bool, NUMBER_OF_FLAGS>;
using FlagsPtr = std::shared_ptr<Flags>;

class Thread {
private:
    std::thread worker_;
    StatCode stat_;
    Flags flags_;
    //std::mutex thread_mutex_;
    Register program_counter_;
public:
    // constructor
    Thread(RegisterBlock& block);
    Thread(size_t address);

    // destructor
    ~Thread();
    
    // getters
    std::string getId() const;
    Register getPC() const;
    StatCode getStat() const;

    // setters
    void setId(const std::string& id);
    void setPC(const Register pc);
    void setStat(StatCode stat);
    
    // other methods
    void execute();
    void threaLoop();
};


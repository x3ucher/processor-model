#pragma once

#include <thread>
#include <string>
#include <mutex>
#include <functional>

#include "include/registers.hpp"

class Thread {
private:
    std::thread worker_;
    std::mutex thread_mutex_;
    Register program_counter_;
    bool is_ready_ = false;
public:
    // constructor
    Thread(RegisterBlock& block);
    Thread(size_t address);

    // destructor
    ~Thread();
    
    // getters
    std::string getId() const;
    Register getPC() const;

    // setters
    void setId(const std::string& id);
    void setPC(const Register pc);
    
    // other methods
    void execute();
    void threaLoop();
};


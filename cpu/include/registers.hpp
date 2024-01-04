#pragma once

#include "../utils/include/configconst.hpp"

struct Register {
    GPRegister name = GPRegister::r15;
    uint64_t value = 0x00;
    bool lock = false;
};

class RegisterBlock {
private:
    std::array<Register, NUMBER_OF_GPR> registers_;
public:
    // constructors
    RegisterBlock();
    RegisterBlock(std::array<uint64_t, NUMBER_OF_GPR>& values);

    // destructors
    // ~RegisterBlock();

    // getters
    Register getRegister(GPRegister name);
    bool isLocked(GPRegister name);

    // setters
    void setRegister(GPRegister name, uint64_t value);
    void setRegister(GPRegister name, uint64_t value, bool lock);
    void setRegisters(const std::array<Register, NUMBER_OF_GPR>& registers);

    // other methods
    void lockRegister(GPRegister name);
    void lockAll();

    void unlockRegister(GPRegister name);
    void unlockAll();
};

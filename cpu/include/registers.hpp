#pragma once

#include "../../utils/include/configconst.hpp"

struct Register {
    GPRegister name = GPRegister::r15;
    int value = 0x00;
    bool lock = false;
};

class RegisterBlock {
private:
    std::array<Register, NUMBER_OF_GPR> registers_;
public:
    // constructors
    RegisterBlock();
    RegisterBlock(const std::array<int, NUMBER_OF_GPR>& values);

    // getters
    Register getRegister(GPRegister name) const;
    bool isLocked(GPRegister name);

    // setters
    void setRegister(GPRegister name, int value);
    void setRegister(GPRegister name, int value, bool lock);
    void setRegisters(const std::array<Register, NUMBER_OF_GPR>& registers);

    // other methods
    void lockRegister(GPRegister name);
    void lockAll();

    void unlockRegister(GPRegister name);
    void unlockAll();
};

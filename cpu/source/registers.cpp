#include "../include/registers.hpp"

// constructors
RegisterBlock::RegisterBlock() {
    for (size_t i = 0; i < NUMBER_OF_GPR; i++) {
        registers_[i] = { static_cast<GPRegister>(i), 0, false };
    }
}

RegisterBlock::RegisterBlock(const std::array<int, NUMBER_OF_GPR>& value) {
    for (size_t i = 0; i < NUMBER_OF_GPR; i++) {
        register_[i] = { static_cast<GPRegister>(i), value[i], false };
    }
}

// getters
Register RegisterBlock::getRegister(GPRegister name) const {
    return registers_[static_cast<size_t>(name)];
}

bool isLocked(GPRegister name) const {
    return registers_[static_cast<size_t>(name)].lock;
}

// setters
void RegisterBlock::setRegister(GPRegister name, int value) {
    //if (isLocked(name)) { throw std::invalid_argument("register is locked"); }
    registers_[static_cast<size_t>(name)] = { name, value, false };
}

void RegisterBlock::setRegister( GPRegister name, int value, bool lock ) {
    registers_[static_cast<size_t>(name)] = { name, value, lock };
} 

void RegisterBlock::setRegisters(const std::array<Register, NUMBER_OF_GPR>& registers) {
    registers_ = register;
}

// other methods 
void RegisterBlock::lockRegister(GPRegister name) {
    registers_[static_cast<size_t>(name)].lock = true;
}

void RegisterBlock::lockAll() {
    for (size_t i; i < NUMBER_OF_GPR; i++) {
        registers_[i].lock = true;
    }
}

void RegisterBlock::unlockRegister(GPRegister name) {
    registers_[static_cast<size_t>(name)].lock = false;
}

void RegisterBlock::unlockAll() {
    for (size_t i; i < NUMBER_OF_GPR; i++) {
        registers_[i].lock = false;
    }
}
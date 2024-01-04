#ifndef CONFIG_CONST_H
#define CONFIG_CONST_H

#include <utility>
#include <vector>
#include <array>
#include <memory>

enum class OperandType{
    REGISTER_OPERAND = 253,
    MEMORY_OPERAND,
    IMMEDIATE_OPERAND
};

typedef ;

constexpr int NUMBER_OF_FLAGS = 4;

// number of general purpose registers
constexpr int NUMBER_OF_GPR = 16;

// general purpose registers in 64-bit
enum class GPRegister {
    rax,
    rbx,
    rcx,
    rdx,
    rsp,
    rbp,
    rsi,
    rdi,
    r8,
    r9,
    r10,
    r11,
    r12,
    r13,
    r14,
    r15
};

enum class ConditionFlags {
    ZF, // zero
    CF, // carry
    SF, // sign
    OF // overflow
};

enum class StatCode {
    AOK, // success
    HLT, // halt
    ADR, // invalid adress
    INS // invalid instruction
};

// token type for lexer
enum class SpecCode {
    MNEMONIC, // 0
    REGISTER, // 1
    ADDRESS,
    NUMBER,
    LABEL,
    DIRECTORY, // 5
    END,
    UNKNOWN,
};

struct Token {
    SpecCode type;
    std::string name;
};

#endif // CONFIG_CONST_H
#pragma once

#include <utility>
#include <vector>
#include <array>
#include <memory>

/**
 * @enum OperandType
 * @brief Enumeration for different operand types.
 */
enum class OperandType{
    REGISTER_OPERAND = 253,
    MEMORY_OPERAND,
    IMMEDIATE_OPERAND
};
//=====================================================//

constexpr int NUMBER_OF_FLAGS = 4; /**< Number of flags. */

// number of general purpose registers
constexpr int NUMBER_OF_GPR = 16; /**< Number of general-purpose registers. */
//=====================================================//

// general purpose registers in 64-bit
/**
 * @enum GPRegister
 * @brief Enumeration for general-purpose registers in 64-bit.
 */
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
//=====================================================//

/**
 * @enum ConditionFlags
 * @brief Enumeration for condition flags.
 */
enum class ConditionFlags {
    ZF, // zero
    CF, // carry
    SF, // sign
    OF // overflow
};

/**
 * @enum StatCode
 * @brief Enumeration for status codes.
 */
enum class StatCode {
    AOK, // success
    HLT, // halt
    ADR, // invalid adress
    INS // invalid instruction
};
//=====================================================//


// token type for lexer
/**
 * @enum SpecCode
 * @brief Enumeration for token types used in the lexer.
 */
enum class SpecCode {
    MNEMONIC,   // 0
    REGISTER,   // 1
    ADDRESS,    // 2
    NUMBER,     // 3
    LABEL,      // 4 
    DIRECTORY,  // 5
    END,        // 6
    UNKNOWN     // 7
};
//=====================================================//

/**
 * @struct Token
 * @brief Structure representing a token with its type and name.
 */
struct Token {
    SpecCode type;
    std::string name;
};

using TokenLine = std::vector<Token>; /**< Type alias for a line of tokens. */
//=====================================================//

/**
 * @brief Checks if a string represents an integer.
 * @param s The string to be checked.
 * @return True if the string is an integer, false otherwise.
 */
static bool isInteger(const std::string& s) {
    try {
        std::stoi(s);
        return true;
    } 
    catch(const std::invalid_argument& e) {
        return false;
    } 
    catch(const std::out_of_range& e) {
        return false;
    }
}

/**
 * @brief Converts a string to an integer.
 * @param s The string to be converted.
 * @return The integer value.
 * @throw std::invalid_argument if the conversion fails.
 */
static int toInteger(const std::string& s) {
    try {
        int val = std::stoi(s);
        return val;
    } 
    catch(...) {
        throw std::invalid_argument("argument isn't integer");
    } 
}
//=====================================================//

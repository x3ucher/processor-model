#pragma once

#include "../../cpu/include/memory.hpp"
#include "../../cpu/include/registers.hpp"
//#include "../../asm/include/assembler.hpp"

/**
 * @class Operand
 * @brief Base class for representing operands in instructions.
 */
class Operand {
protected:
    OperandType type_; /**< Operand type. */
    RegisterBlockPtr registers; /**< Pointer to the block of general-purpose registers. */
    DataMemoryPtr memory; /**< Pointer to data memory. */
public:
    /**
     * @brief Constructor for Operand.
     * @param reg Pointer to the block of general-purpose registers.
     * @param ram Pointer to data memory.
     */
    Operand(RegisterBlockPtr& reg, DataMemoryPtr& ram) : registers(reg), memory(ram) {}
    
    /**
     * @brief Virtual destructor for Operand.
     */
    virtual ~Operand() = default;

    /**
     * @brief Gets the type of the operand.
     * @return The type of the operand.
     */
    OperandType getType() const;

    /**
     * @brief Gets the value of the operand.
     * @return The value of the operand.
     */
    virtual int getValue() const = 0;

    /**
     * @brief Sets the value of the operand.
     * @param value The value to set.
     */
    virtual void setValue(int value) = 0;
};
//==================================================//

/**
 * @class RegisterOperand
 * @brief Class for representing register operands in instructions.
 */
class RegisterOperand : public Operand {
private:
    GPRegister register_; /**< The specific general-purpose register. */
public:
    /**
     * @brief Constructor for RegisterOperand.
     * @param token The token containing register information.
     * @param reg Pointer to the block of general-purpose registers.
     * @param ram Pointer to data memory.
     */
    RegisterOperand(const Token& token, RegisterBlockPtr& reg, DataMemoryPtr& ram);

    /**
     * @brief Gets the value of the register operand.
     * @return The value of the register operand.
     */
    int getValue() const override;

    /**
     * @brief Sets the value of the register operand.
     * @param value The value to set.
     */
    void setValue(int value) override;
};
//==================================================//

/**
 * @class MemoryOperand
 * @brief Class for representing memory operands in instructions.
 */
class MemoryOperand : public Operand {
private:
    size_t address_; /**< The memory address. */
public:
    /**
     * @brief Constructor for MemoryOperand.
     * @param token The token containing memory address information.
     * @param reg Pointer to the block of general-purpose registers.
     * @param ram Pointer to data memory.
     */
    MemoryOperand(const Token& token, RegisterBlockPtr& reg, DataMemoryPtr& ram);
    
    /**
     * @brief Gets the value stored at the memory address.
     * @return The value stored at the memory address.
     */
    int getValue() const override;
    
    /**
     * @brief Sets the value at the memory address.
     * @param value The value to set.
     */
    void setValue(int value) override;
    
    /**
     * @brief Gets the memory address.
     * @return The memory address.
     */
    size_t getAddress() const;
};
//==================================================//

/**
 * @class ImmediateOperand
 * @brief Class for representing immediate operands in instructions.
 */
class ImmediateOperand : public Operand {
private:
    int value_; /**< The immediate value. */
public:
    /**
     * @brief Constructor for ImmediateOperand.
     * @param token The token containing immediate value information.
     * @param reg Pointer to the block of general-purpose registers.
     * @param ram Pointer to data memory.
     */
    ImmediateOperand(const Token& token, RegisterBlockPtr& reg, DataMemoryPtr& ram);

    /**
     * @brief Gets the immediate value.
     * @return The immediate value.
     */
    int getValue() const override;

    /**
     * @brief Sets the immediate value.
     * @param value The value to set.
     */
    void setValue(int value) override;
};
//==================================================//

using OperandPtr = std::shared_ptr<Operand>; /**< Type alias for shared pointer to Operand. */
//==================================================//
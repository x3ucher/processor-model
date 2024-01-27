#pragma once

#include "configconst.hpp"

#include <unordered_map>
#include <iostream>
#include <cstring>
#include <sstream>
#include <fstream>

using BinData = std::pair<SpecCode, std::vector<uint8_t>>;
//==================================================//

// LabelMap
/**
 * @class LabelMap
 * @brief Manages labels and their corresponding addresses.
 */
class LabelMap {
private:
    std::unordered_map<std::string, int> labels; /**< Map to store labels and their addresses. */
public:
    /**
     * @brief Adds a label and its address to the map.
     * @param label The label to be added.
     * @param adr The address associated with the label.
     */
    void pushLabel(const std::string& label, size_t adr) {
        labels[label] = adr;
    }

    /**
     * @brief Gets the address associated with a label.
     * @param label The label to find the address for.
     * @return The address associated with the label. Returns -1 if the label is not found.
     */
    int getAddress(const std::string& label) {
        auto it = labels.find(label);
        if (it != labels.end()) { return it->second; } 
        else { return -1; }
    }
};
//==================================================//

// TokenTypeMap
/**
 * @class TokenTypeMap
 * @brief Maps mnemonics to their corresponding SpecCode values.
 */
class TokenTypeMap {
private:
    std::string filename; /**< Filepath for the token type configuration file. */
    std::unordered_map<std::string, SpecCode> token_code_; /**< Map to store mnemonics and their SpecCode values. */
public:
    /**
     * @brief Constructor that reads mnemonics and their SpecCode values from a file.
     * @throw std::runtime_error if the file cannot be opened.
     */
    TokenTypeMap() {
        filename = "../config/tokentype.txt";
        std::ifstream file(filename);
        if (file.is_open()) {
            std::string mnemonic;
            int opcode;
            while (file >> mnemonic >> opcode) {
                token_code_[mnemonic] = static_cast<SpecCode>(opcode);
            }
            file.close();
        } 
        else {
            throw std::runtime_error("unable to open tokentype.txt");
        }
    }

    /**
     * @brief Finds the SpecCode value for a given mnemonic.
     * @param mnemonic The mnemonic to find the SpecCode for.
     * @return The SpecCode value corresponding to the mnemonic. Returns SpecCode::UNKNOWN if not found.
     */
    SpecCode findOpcode(const std::string& mnemonic) {
        if (token_code_.find(mnemonic) != token_code_.end()) {
            return token_code_[mnemonic];
        } 
        else {
            return SpecCode::UNKNOWN;
        }
    }
};
//==================================================//

// BinCodeMap
/**
 * @class BinCodeMap
 * @brief Maps mnemonics to their corresponding uint8_t values.
 */
class BinCodeMap {
private:
    std::string filename; /**< Filepath for the binary code configuration file. */
    std::unordered_map<std::string, uint8_t> mnemonic_code_; /**< Map to store mnemonics and their uint8_t values. */
public:
    /**
     * @brief Constructor that reads mnemonics and their uint8_t values from a file.
     * @throw std::runtime_error if the file cannot be opened.
     */
    BinCodeMap() {
        filename = "../config/bincode.txt";
        std::ifstream file(filename);
        if (file.is_open()) {
            std::string mnemonic;
            int opcode;
            while (file >> mnemonic >> opcode) {
                mnemonic_code_[mnemonic] = static_cast<uint8_t>(opcode);
            }
            file.close();
        } 
        else {
            throw std::runtime_error("unable to open bincode.txt");
        }
    }

    /**
     * @brief Finds the uint8_t value for a given mnemonic.
     * @param mnemonic The mnemonic to find the uint8_t value for.
     * @return The uint8_t value corresponding to the mnemonic. Returns 255 if not found.
     */
    uint8_t findOpcode(const std::string& mnemonic) {
        if (mnemonic_code_.find(mnemonic) != mnemonic_code_.end()) {
            return mnemonic_code_[mnemonic];
        } 
        else {
            return 255; 
        }
    }
};
//==================================================//

/**
 * @class IBinary
 * @brief Interface for handling binary data.
 */
class IBinary : public BinCodeMap {
public:    
    /**
     * @brief Initializes binary data with a SpecCode and value.
     * @param type The SpecCode value.
     * @param val The value associated with the SpecCode.
     * @return The initialized binary data.
     */
    BinData initBinary(SpecCode type, const std::string& val);

    /**
     * @brief Initializes binary data with an integer value.
     * @param value The integer value.
     * @return The initialized binary data.
     */
    BinData initBinary(int value);

    /**
     * @brief Initializes an integer value from binary data.
     * @param data The binary data.
     * @return The initialized integer value.
     */
    int initFromBinary(const BinData& data) const;
};
//==================================================//
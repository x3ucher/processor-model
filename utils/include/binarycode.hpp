#include "configconst.hpp"

#include <unordered_map>
#include <iostream>
#include <cstring>
#include <sstream>
#include <fstream>

using BinData = std::pair<SpecCode, std::vector<uint8_t>>;
//==================================================//

// LabelMap
class LabelMap {
private:
    std::unordered_map<std::string, int> labels;
public:
    void pushLabel(const std::string& label, size_t adr) {
        labels[label] = adr;
    }

    int getAddress(const std::string& label) {
        auto it = labels.find(label);
        if (it != labels.end()) { return it->second; } 
        else { return -1; }
    }
};
//==================================================//

// TokenTypeMap
class TokenTypeMap {
private:
    std::string filename;
    std::unordered_map<std::string, SpecCode> token_code_;
public:
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
class BinCodeMap {
private:
    std::string filename;
    std::unordered_map<std::string, uint8_t> mnemonic_code_;
public:
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

class IBinary : public BinCodeMap {
public:    
    BinData initBinary(SpecCode type, const std::string& val);
    BinData initBinary(int value);
    int initFromBinary(const BinData& data);
};
//==================================================//
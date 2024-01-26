#include "../include/binarycode.hpp"

BinData IBinary::initBinary(int value) {
    std::vector<uint8_t> binary(sizeof(int));
    std::memcpy(binary.data(), &value, sizeof(int));
    return { SpecCode::NUMBER, binary };
}

BinData IBinary::initBinary(SpecCode type, const std::string& val) {
    std::vector<uint8_t> binary;
    if (type == SpecCode::MNEMONIC || type == SpecCode::DIRECTORY || type == SpecCode::REGISTER) {
        uint8_t opcode = findOpcode(val);
        if (opcode == 0xFF) {
            throw std::invalid_argument("invalid command");
        }
        binary.push_back(opcode);
    }
    else if (type == SpecCode::NUMBER) {
        int value = std::stoi(val);
        return initBinary(value);
    }
    else if (type == SpecCode::ADDRESS || type == SpecCode::LABEL) {
        int value = std::stoi(val);
        binary.resize(sizeof(size_t));
        std::memcpy(binary.data(), &value, sizeof(size_t));
    }
    else { binary.push_back(0xFF); }
    return { type, binary };
}

int IBinary::initFromBinary(const BinData& data) const {
    if (data.first == SpecCode::NUMBER) {
        int value;
        std::memcpy(&value, data.second.data(), sizeof(int));
        return value;
    }
    throw std::invalid_argument("invalid command");
}
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
    if (type == SpecCode::NUMBER || type == SpecCode::ADDRESS || type == SpecCode::LABEL) {
        int value = std::stoi(val);
        return initBinary(value);
    }
    else { binary.push_back(0xFF); }
    return { type, binary };
}


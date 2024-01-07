#include "../include/instructions.hpp"

Instruction::Instruction(const TokenLine& tokens) {
    if (tokens[0].type == SpecCode::MNEMONIC || tokens[0].type == SpecCode::DIRECTORY) {
        opcode = tokens[0].name;
        

    }
    else {

    }
}
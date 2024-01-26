#pragma once

#include "../../utils/include/configconst.hpp"
#include "../../utils/include/binarycode.hpp"
//#include "../../instructions/include/instructions.hpp"
//#include "../../instructions/include/commands.hpp"
#include "../../cpu/include/processor.hpp"

#include <functional>

enum class MaskInstr {
    L_, // label
    D_, // directory
    RI, // register, immediate
    RR, // register, register
    RA, // register, address
    AI, // address, immediate
    AR, // address, register
    AA, // address, address
    R_, // register
    A_, // address 
    CL, // command with label (jump, thread init)
    C_, // command without argument (unary command, thread term)
    XX // unknown/error
};

using TokenLine = std::vector<Token>;
using ProgramLayout = std::vector<std::pair<MaskInstr, TokenLine>>;
//======================================================//


class Lexer : public TokenTypeMap  {
public:
    std::vector<TokenLine> lines;
    explicit Lexer(const std::string& filename); 

    Token createToken(const std::string& token);
    TokenLine tokenizeLine(const std::string& line);
};
//======================================================//

/*
using CommandCreator = std::function<CommandPtr()>;
//example
//CommandPtr command = op_table.commandCreate(0x01);

class CodeTable {
private:
    std::unordered_map<uint8_t, CommandCreator> opcode_to_command_;
public:
    CodeTable();    
    CommandPtr commandCreate(Instruction& instr);
};

//======================================================//


class Assemble : protected Lexer, protected CodeTable {
private:    
    CPU cpu;
    LabelMap value_names;
    LabelMap labels;
public:
    void cleaner();
    void masking();
    void processDirectory(TokenLine line);
    Assemble(const std::string& filename_, CPU& cpu_) : Lexer(filename_), cpu(cpu_) {}
    ProgramMemory interpreter();
};
*/
//======================================================//
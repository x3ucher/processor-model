#pragma once

#include "../../utils/include/configconst.hpp"
#include "../../utils/include/binarycode.hpp"
#include "../../instructions/include/instructions.hpp"
#include "../../instructions/include/commands.hpp"
//#include "../../cpu/include/processor.hpp"

#include <memory>
#include <functional>
#include <thread>

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


using ProgramLayout = std::vector<std::pair<MaskInstr, TokenLine>>;
//======================================================//

// -1 метка не найдена
// > 0 адрес метки
// -2 метку добавили без адреса
class Lexer : public TokenTypeMap  {
protected:
    LabelMap value_names;
    LabelMap labels;
public:
    std::vector<TokenLine> lines;
    explicit Lexer(const std::string& filename); 

    Token createToken(const std::string& token);
    TokenLine tokenizeLine(const std::string& line);
};
//======================================================//


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


struct LabelLine{
    bool del = false;
    size_t j = 0;
};


class Assemble : public Lexer, protected CodeTable {
private:    
    CPUPtr cpu;
    // LabelMap value_names;
    // LabelMap labels;
    void cleanerThread(std::vector<TokenLine>& lines, std::vector<LabelLine>& collector, size_t start, size_t end);
public:
    void cleaner();
    void processDirectory(TokenLine line);
    Assemble(const std::string& filename_, CPUPtr& cpu_) : Lexer(filename_), cpu(cpu_) {}
    ProgramMemory interpreter();
};

//======================================================//
#pragma once

#include "../../utils/include/configconst.hpp"
#include "../../utils/include/binarycode.hpp"
#include "../../cpu/include/processor.hpp"

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

class Lexer : public TokenTypeMap  {
public:
    std::vector<TokenLine> lines;
    explicit Lexer(const std::string& filename); 

    Token createToken(const std::string& token);
    TokenLine tokenizeLine(const std::string& line);
};


class Assemble : protected Lexer {
private:    
    //RAM ram;
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
#pragma once

#include "../utils/include/configconst.hpp"
#include "../utils/include/binarycode.hpp"
#include "../cpu/include/processor.hpp"

using TokenLine = std::vector<Token>;

class Lexer {
    std::vector<TokenLine> lines;
    explicit Lexer(const std::string& filename); 

    Token createToken_(const std::string& token);
    TokenLine tokenizeLine(const std::string& line);
};


class Assemble : protected Lexer{
private:    
    RAM ram;
public:
    explicit Assemble(const std::string& filename, RAM& ram);
};
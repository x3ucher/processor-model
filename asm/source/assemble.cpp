#include "../include/assembler.hpp"

explicit Lexer::Lexer(const std::string& filename){
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::invalid_argument("invalid filename");
    }

    std::string line; 
    while (std::getline(file, line)) {
        if (line.front() == ';') { continue; }
        lines.push_back(tokenizeLine(line));
    }

    TokenLine last; 
    last.push_back({ SpecCode::END, "" });
    lines.push_back(last);
    file.close();
}

TokenLine Lexer::tokenizeLine(const std::string& line) {
    TokenLine cur_line;
    std::istringstream iss(line);
    std::string token;
    while(iss >> token) {
        if (token.front() == ';') { break; }
        cur_line.push_back(createToken(token));
    }
    return cur_line;
}

Token Lexer::createToken(const std::string& token) {
    if (token.back() == ':') {
        return { SpecCode::LABEL, token.substr(0, token.size() - 1) }; // .substr(0, token.size() - 1)
    }
    std::string new_token = token;
    if (token.back() == ','){
        new_token = token.substr(0, token.size() - 1);
    }
    if (new_token.front() == '[' && new_token.back() == ']'){
        std::string address = new_token.substr(1, new_token.size() - 2);
        if (!isInteger(address)) {
            throw std::invalid_argument("invalid asm code");
        }
        return { SpecCode::ADDRESS, address };
    }
    return { findOpcode(new_token), new_token };
}


void Assemble::cleaner() {
    // label declaration
    for (size_t i = 0; i < lines.size(); i++) {
        if (lines[i][0].type == SpecCode::LABEL) {
            if (lines[i].size() == 1) {
                labels.pushLabel(lines[i][0].name, i);
            }
            else if (lines[i][1].type == SpecCode::DIRECTORY) {
                processDirectory(lines[i]);
            }
            else { 
                throw std::invalid_argument("invalid asm code");
            }
            lines.erase(lines.begin() + i);
            i--;
            continue;
        }
        break;
    }
    for (size_t i = 0; i < lines.size(); i++) {
        bool flag = false;
        for (size_t j = 0; j < lines[i].size(); j++) {
            if (lines[i][j].type == SpecCode::UNKNOWN) {
                if (isInteger(lines[i][j].name)) {
                    lines[i][j].type = SpecCode::NUMBER;
                    continue;
                }
                int adr = labels.getAddress(lines[i][j].name);
                if (adr != -1) {
                    lines[i][j] = { SpecCode::LABEL, std::to_string(adr) };
                    continue;
                }
                adr = value_names.getAddress(lines[i][j].name);
                if (adr != -1) {
                    lines[i][j] = { SpecCode::ADDRESS, std::to_string(adr) };
                    continue;
                }
                flag = true;
                break;
            }
            if (flag) { throw std::invalid_argument("invalid asm code"); }
        }
    }
}
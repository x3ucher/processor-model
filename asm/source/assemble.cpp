#include "../include/assembler.hpp"

// Lexer
Lexer::Lexer(const std::string& filename){
    std::ifstream file(filename); // open file
    if (!file.is_open()) {
        throw std::invalid_argument("invalid filename");
    }

    std::string line; // parse file to array of lines
    while (std::getline(file, line)) {
        if (line.empty()) { continue; }
        std::size_t firstNonSpace = line.find_first_not_of(" \t\n\r\f\v");
        if (firstNonSpace != std::string::npos && line[firstNonSpace] == ';') { continue; } // comment
        lines.push_back(tokenizeLine(line));
    }

    TokenLine last; // last line
    last.push_back({ SpecCode::END, "" });
    lines.push_back(last);
    file.close();
}

TokenLine Lexer::tokenizeLine(const std::string& line) {
    TokenLine cur_line; 
    std::istringstream iss(line);
    std::string token;
    while(iss >> token) { // patse line to tokens
        if (token.front() == ';') { break; } // comment
        cur_line.push_back(createToken(token));
    }
    return cur_line;
}

Token Lexer::createToken(const std::string& token) {
    if (token.back() == ':') { // label declarition
        labels.pushLabel(token.substr(0, token.size() - 1), -2); 
        return { SpecCode::LABEL, token.substr(0, token.size() - 1) }; // .substr(0, token.size() - 1)
    }
    std::string new_token = token;
    if (token.back() == ','){ // enumeration
        new_token = token.substr(0, token.size() - 1);
    }
    if (new_token.front() == '[' && new_token.back() == ']'){
        std::string address = new_token.substr(1, new_token.size() - 2);
        if (!isInteger(address)) {
            throw std::invalid_argument("invalid asm code");
        }
        return { SpecCode::ADDRESS, address };
    }
    return { findOpcode(new_token), new_token }; // numbers, labels, dirrectories and names
}
//===========================================================//

// Assemble
void Assemble::processDirectory(TokenLine line) {
    Token first = line[0];
    line.erase(line.begin());
    for (size_t i = 1; i < line.size(); i++) {
        if (line[i].type == SpecCode::UNKNOWN && isInteger(line[i].name)) {
            line[i].type = SpecCode::NUMBER;
        }
        else if (line[i].type != SpecCode::NUMBER) { 
            throw std::invalid_argument("invalid asm code: dir");
        }
    }
    Instruction instr(line, cpu);
    CommandPtr command = std::move(commandCreate(instr));
    command->execute(cpu);
    value_names.pushLabel(first.name, std::dynamic_pointer_cast<DataDeclaration>(command)->getDataAddress());
}

// Cleaner in 1 pass
/*
void Assemble::cleaner() {
    for (size_t i = 0; i < lines.size(); i++) {
        if (lines[i][0].type == SpecCode::UNKNOWN) {
            if (lines[i][1].type == SpecCode::DIRECTORY) { // data declaration
                processDirectory(lines[i]);
            }
            lines.erase(lines.begin() + i); // cleaning, because if its a label =>
            i--; // remember the address, if its a data declaration => is a preproc instr
            continue;
        }
        if (lines[i][0].type == SpecCode::LABEL ) {
            labels.pushLabel(lines[i][0].name, i);
            lines.erase(lines.begin() + i); // cleaning, because if its a label =>
            i--; // remember the address, if its a data declaration => is a preproc instr
            continue;
        }
    }
    int deleted = 0;
    for (size_t i = 0; i < lines.size(); i++) {
        for (size_t j = 0; j < lines[i].size(); j++) {
            if (lines[i][j].type == SpecCode::UNKNOWN) { // unknown tokens
                if (isInteger(lines[i][j].name)) {
                    lines[i][j].type = SpecCode::NUMBER; // number
                    continue;
                }
                int adr = labels.getAddress(lines[i][j].name); // check label
                if (adr > -1) {
                    lines[i][j] = { SpecCode::LABEL, std::to_string(adr - deleted) };
                    continue;
                }
                adr = value_names.getAddress(lines[i][j].name); // check value name
                if (adr != -1) {
                    lines[i][j] = { SpecCode::ADDRESS, std::to_string(adr) };
                    continue;
                }
                //flag = true; // still unknown => error
                break;
            }
            if (lines[i][0].type == SpecCode::UNKNOWN) {
                lines.erase(lines.begin() + i); // cleaning, because if its a label =>
                i--;
                deleted++;
            }
        }
    }
}*/

// Cleaner for multithread
void Assemble::cleanerThread(std::vector<TokenLine>& lines, std::vector<LabelLine>& collector, size_t start, size_t end) {
    for (size_t i = start; i < end; i++) {
        for (size_t j = 0; j < lines[i].size(); j++) {
            if (lines[i][j].type == SpecCode::UNKNOWN) { // unknown tokens
                if (isInteger(lines[i][j].name)) {
                    lines[i][j].type = SpecCode::NUMBER; // number
                    continue;
                }
                int adr = labels.getAddress(lines[i][j].name); // check label
                if (adr > -1) {
                    lines[i][j] = { SpecCode::LABEL, lines[i][j].name };
                    collector[i] = { false, j };
                    continue;
                }
                adr = value_names.getAddress(lines[i][j].name); // check value name
                if (adr != -1) {
                    lines[i][j] = { SpecCode::ADDRESS, std::to_string(adr) };
                    continue;
                }
                collector[i] = { true, 0 };
            }
            if (lines[i][0].type == SpecCode::UNKNOWN) {
                collector[i] = { true, 0 };
            }
        }
    }
}

void Assemble::cleaner() {
    for (size_t i = 0; i < lines.size(); i++) {
        if (lines[i][0].type == SpecCode::UNKNOWN) {
            if (lines[i][1].type == SpecCode::DIRECTORY) { // data declaration
                processDirectory(lines[i]);
            }
            lines.erase(lines.begin() + i); // cleaning, because if its a label =>
            i--; // remember the address, if its a data declaration => is a preproc instr
            continue;
        }
        if (lines[i][0].type == SpecCode::LABEL ) {
            labels.pushLabel(lines[i][0].name, i);
            lines.erase(lines.begin() + i); // cleaning, because if its a label =>
            i--; // remember the address, if its a data declaration => is a preproc instr
            continue;
        }
    }

    const size_t numThreads = std::thread::hardware_concurrency();
    const size_t chunkSize = lines.size() / numThreads;

    std::vector<std::thread> threads;
    std::vector<size_t> threadStarts;

    std::vector<LabelLine> collector(lines.size());

    //
    for (size_t i = 0; i < numThreads; ++i) {
        threadStarts.push_back(i * chunkSize);
        if (i == numThreads - 1) {
            threads.emplace_back(&Assemble::cleanerThread, this, std::ref(lines), std::ref(collector), i * chunkSize, lines.size());
        } else {
            threads.emplace_back(&Assemble::cleanerThread, this, std::ref(lines), std::ref(collector), i * chunkSize, (i + 1) * chunkSize);
        }
    }

    for (auto& thread : threads) {
        thread.join();
    }
    //

    size_t deleted = 0;
    for  (size_t i = 0; i < lines.size(); i++) {
        if (collector[i].del) { 
            deleted++;
            lines.erase(lines.begin() + i);
            collector.erase(collector.begin() + i);
            i--;
            continue;
        }
        if (collector[i].j != 0) {
            int adr = labels.getAddress(lines[i][collector[i].j].name);
            lines[i][collector[i].j] = { SpecCode::LABEL, std::to_string(adr - deleted) };
        }
    }
}


// Cleaner for multithreading
/*
void Assemble::cleaner() {
    for (size_t i = 0; i < lines.size(); i++) {
        if (lines[i][0].type == SpecCode::UNKNOWN) {
            if (lines[i][1].type == SpecCode::DIRECTORY) { // data declaration
                processDirectory(lines[i]);
            }
            lines.erase(lines.begin() + i); // cleaning, because if its a label =>
            i--; // remember the address, if its a data declaration => is a preproc instr
            continue;
        }
        if (lines[i][0].type == SpecCode::LABEL ) {
            labels.pushLabel(lines[i][0].name, i);
            lines.erase(lines.begin() + i); // cleaning, because if its a label =>
            i--; // remember the address, if its a data declaration => is a preproc instr
            continue;
        }
    }
    std::vector<LabelLine> collector(lines.size());
    for (size_t i = 0; i < lines.size(); i++) {
        for (size_t j = 0; j < lines[i].size(); j++) {
            if (lines[i][j].type == SpecCode::UNKNOWN) { // unknown tokens
                if (isInteger(lines[i][j].name)) {
                    lines[i][j].type = SpecCode::NUMBER; // number
                    continue;
                }
                int adr = labels.getAddress(lines[i][j].name); // check label
                if (adr > -1) {
                    lines[i][j] = { SpecCode::LABEL, lines[i][j].name };
                    collector[i] = { false, j };
                    continue;
                }
                adr = value_names.getAddress(lines[i][j].name); // check value name
                if (adr != -1) {
                    lines[i][j] = { SpecCode::ADDRESS, std::to_string(adr) };
                    continue;
                }
                collector[i] = { true, 0 };
            }
            if (lines[i][0].type == SpecCode::UNKNOWN) {
                collector[i] = { true, 0 };
            }
        }
    }
    size_t deleted = 0;
    for  (size_t i = 0; i < lines.size(); i++) {
        if (collector[i].del) { 
            deleted++;
            lines.erase(lines.begin() + i);
            collector.erase(collector.begin() + i);
            i--;
            continue;
        }
        if (collector[i].j != 0) {
            int adr = labels.getAddress(lines[i][collector[i].j].name);
            lines[i][collector[i].j] = { SpecCode::LABEL, std::to_string(adr - deleted) };
        }
    }
}
*/

ProgramMemory Assemble::interpreter() {
    ProgramMemory program;
    cleaner();
    for (size_t i = 0; i < lines.size(); i++) {
        Instruction instr(lines[i], cpu);
        CommandPtr command = std::move(commandCreate(instr));
        program.pushCommand(command);
    }
    return program;
}

//===========================================================//

// CodeTable methods

CodeTable::CodeTable() {
    opcode_to_command_[0x01] = []() { return std::make_shared<MOV>(); };
    // arithmetic
    opcode_to_command_[0x02] = []() { return std::make_shared<ADD>(); };
    opcode_to_command_[0x03] = []() { return std::make_shared<SUB>(); };
    opcode_to_command_[0x04] = []() { return std::make_shared<INC>(); };
    opcode_to_command_[0x05] = []() { return std::make_shared<DEC>(); };
    // logic
    opcode_to_command_[0x06] = []() { return std::make_shared<NOT>(); };
    opcode_to_command_[0x07] = []() { return std::make_shared<AND>(); };
    opcode_to_command_[0x08] = []() { return std::make_shared<OR>(); };
    opcode_to_command_[0x09] = []() { return std::make_shared<XOR>(); };
    opcode_to_command_[0x0A] = []() { return std::make_shared<CMP>(); };
    // shifts
    opcode_to_command_[0x0B] = []() { return std::make_shared<SHL>(); };
    opcode_to_command_[0x0C] = []() { return std::make_shared<SHR>(); };
    // jumps
    opcode_to_command_[0x0D] = []() { return std::make_shared<JMP>(); };
    opcode_to_command_[0x0E] = []() { return std::make_shared<JE>(); };
    opcode_to_command_[0x0F] = []() { return std::make_shared<JNE>(); };
    opcode_to_command_[0x10] = []() { return std::make_shared<JG>(); };
    opcode_to_command_[0x11] = []() { return std::make_shared<JGE>(); };
    opcode_to_command_[0x12] = []() { return std::make_shared<JL>(); };
    opcode_to_command_[0x13] = []() { return std::make_shared<JLE>(); };
    // data definition
    //opcode_to_command_[0x14] = []() { return std::make_shared<DB>(); };
    //opcode_to_command_[0x15] = []() { return std::make_shared<DW>(); };
    opcode_to_command_[0x16] = []() { return std::make_shared<DD>(); };
    // misc
    opcode_to_command_[0x17] = []() { return std::make_shared<HLT>(); };
    //opcode_to_command_[0x18] = []() { return std::make_shared<ThreadInit>(); };
    //opcode_to_command_[0x19] = []() { return std::make_shared<ThreadTerminate>(); };
}


CommandPtr CodeTable::commandCreate(Instruction& instr){
    auto it = opcode_to_command_.find(instr.getOpcode());
    if (it != opcode_to_command_.end()) {
        CommandPtr command = it->second();
        command->setInstruction(instr);
        return command;
    }
    throw std::runtime_error("invalid opcode");
} 
//===========================================================//
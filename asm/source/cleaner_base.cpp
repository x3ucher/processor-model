#include "../include/assembler.hpp"


// Cleaner in 1 pass
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
}
#pragma once

#include "../utils/include/configconst.hpp"
#include "../utils/include/binarycode.hpp"
#include "../instructions/include/instructions.hpp"

class DataMemory : public IBinary {
private:
    std::vector<BinData> data_;
public:
    DataMemory();

    // getters
    std::vector<BinData> getDump();
    BinData getData(size_t address) const;

    // setters
    void loadDump(const std::vector<BinData>& data);
    void setData(size_t address, const std::vector<BinData>& value);
    void setData(size_t address, BinData value);
};

/* struct RAM {
    LabelMap labels;
    DataMemory memory;
}; */

class ProgramMemory {
private:
    std::vector<CommandPtr> program_;
public:
    ProgramMemory(CPU& cpu);
    void pushCommand(const CommandPtr& command);
    void execute();
};
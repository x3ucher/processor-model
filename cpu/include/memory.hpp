#pragma once

#include "../../utils/include/configconst.hpp"
#include "../../utils/include/binarycode.hpp"
 
#include "iostream"

class DataMemory : public IBinary {
private:
    std::vector<BinData> data_;
public:
    DataMemory();

    // getters
    std::vector<BinData> getDump();
    BinData getData(size_t address) const;
    size_t getLastAddress() { return data_.size() - 1; }

    // setters
    void loadDump(const std::vector<BinData>& data);
    void setData(const BinData& value);
    void setData(size_t address, const BinData& value);
};

using DataMemoryPtr = std::shared_ptr<DataMemory>;
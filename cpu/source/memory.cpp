#include "../include/memory.h"

DataMemory::DataMemory() { data_ = nullptr; }

std::vector<BinData> DataMemory::getDump() {
    return data_;
}

BinData DataMemory::getData(size_t address) const {
    return data_[address];
}

void DataMemory::loadDump(const std::vector<BinData>& data) {
    data_.clear();
    data_ = data;
}

void DataMemory::setData(size_t address, const BinData& value) {
    if (address >= data_.size()) {
        data_.resize(address + 1);
    }
    data_[address] = value;
}

void DataMemory::setData(const BinData& value) {
    data_.push_back(value);
}


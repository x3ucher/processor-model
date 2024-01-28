#include "../include/memory.hpp"

DataMemory::DataMemory() {
    data_.resize(0);
}

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

void DataMemory::print() {
    std::cout << 
    "------------------------------------------------------------------\n";
    std::cout << "memory dump:" << std::endl;
    for (size_t i = 0; i < data_.size(); i++) {
        std::cout << static_cast<int>(data_[i].first) << " ";
        for (size_t j = 0; data_[i].second[j]; j++) {
            std::cout << static_cast<int>(data_[i].second[j]) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << 
    "------------------------------------------------------------------\n";
}

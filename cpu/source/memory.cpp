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
    if (data_.empty()) { std::cout << "memory is empty\n"; }
    std::cout << 
    "------------------------------------------------------------------\n";
    std::cout << "memory dump:" << std::endl;
    for (size_t i = 0; i < data_.size(); i++) {
        std::cout << static_cast<int>(data_[i].first) << " ";
        if (data_[i].second.empty()) { break; }
        for (size_t j = 0; j < data_[i].second.size(); j++) { //39
            std::cout << static_cast<int>(data_[i].second[j]) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << 
    "------------------------------------------------------------------\n";
}

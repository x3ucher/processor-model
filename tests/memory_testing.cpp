#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>

#include "../cpu/include/memory.hpp"

TEST_CASE("DataMemory constructor creates an empty memory", "[DataMemory]") {
    DataMemory memory;
    REQUIRE(memory.getDump().empty());
}

TEST_CASE("DataMemory loadDump loads data correctly", "[DataMemory]") {
    DataMemory memory;
    std::vector<BinData> testData;
    std::string str1 = "23";
    testData.push_back(memory.initBinary(SpecCode::ADDRESS, str1));
    testData.push_back(memory.initBinary(SpecCode::NUMBER, "-345"));

    memory.loadDump(testData);
    REQUIRE(memory.getDump() == testData);
}

TEST_CASE("DataMemory setData adds data to the end of memory", "[DataMemory]") {
    DataMemory memory;
    BinData testData1 = memory.initBinary(SpecCode::ADDRESS, "23");
    BinData testData2 = memory.initBinary(SpecCode::NUMBER, "-345");

    memory.setData(testData1);
    memory.setData(testData2);

    REQUIRE(memory.getLastAddress() == 1);
    REQUIRE(memory.getData(0) == testData1);
    REQUIRE(memory.getData(1) == testData2);
}

TEST_CASE("DataMemory getLastAddress returns the correct last address", "[DataMemory]") {
    DataMemory memory;

    SECTION("Empty memory") {
        REQUIRE(memory.getLastAddress() == static_cast<size_t>(-1)); 
    }

    SECTION("Memory with data") {
        BinData testData1 = memory.initBinary(SpecCode::ADDRESS, "23");
    BinData testData2 = memory.initBinary(SpecCode::NUMBER, "-345");

        memory.setData(testData1);
        REQUIRE(memory.getLastAddress() == 0);

        memory.setData(testData2);
        REQUIRE(memory.getLastAddress() == 1);
    }
}
#define CATCH_CONFIG_MAIN 

#include <catch2/catch.hpp>

#include "../utils/include/binarycode.hpp"


TEST_CASE("IBinary initBinary() Test", "[IBinary]") {
    IBinary binary;

    SECTION("Test integer initialization") {
        int intValue = 42;
        BinData intBinary = binary.initBinary(intValue);

        REQUIRE(intBinary.second.size() == sizeof(int)); 
        REQUIRE(intBinary.first == SpecCode::NUMBER);
        int receivedValue;
        std::memcpy(&receivedValue, intBinary.second.data(), sizeof(int));
        REQUIRE(receivedValue == intValue);
    }
}

// Тесты для класса BinCodeMap
TEST_CASE("BinCodeMap: Opcode lookup") {
    BinCodeMap binCodeMap;

    SECTION("Valid opcode lookup") {
        REQUIRE(binCodeMap.findOpcode("mov") == 1); 
        REQUIRE(binCodeMap.findOpcode("add") == 2);
        REQUIRE(binCodeMap.findOpcode("%rax") == 0);
    }

    SECTION("Invalid opcode lookup") {
        REQUIRE(binCodeMap.findOpcode("INVALID_MNEMONIC") == 255); 
    }
}

// Тесты для класса TokenTypeMap
TEST_CASE("TokenTypeMap: SymbolType lookup") {
    TokenTypeMap tokenTypeMap;

    SECTION("Valid symbol type lookup") {
        REQUIRE(tokenTypeMap.findOpcode("mov") == SpecCode::MNEMONIC); 
        REQUIRE(tokenTypeMap.findOpcode("add") == SpecCode::MNEMONIC);
        REQUIRE(tokenTypeMap.findOpcode("%rax") == SpecCode::REGISTER);
        REQUIRE(tokenTypeMap.findOpcode("dd") == SpecCode::DIRECTORY); 
    }

    SECTION("Invalid symbol type lookup") {
        REQUIRE(tokenTypeMap.findOpcode("INVALID_TYPE") == SpecCode::UNKNOWN);
    }
}

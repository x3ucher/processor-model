#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>

#include "include/processor.hpp"

TEST_CASE("CPU getters and setters", "[CPU]") {
    // Create an instance of CPU
    CPU cpu;

    SECTION("Get and set StatCode") {
        cpu.setStat(StatCode::AOK);
        REQUIRE(cpu.getStat() == StatCode::AOK);

        cpu.setStat(StatCode::HLT);
        REQUIRE(cpu.getStat() == StatCode::HLT);

        cpu.setStat(StatCode::ADR);
        REQUIRE(cpu.getStat() == StatCode::ADR);

        cpu.setStat(StatCode::INS);
        REQUIRE(cpu.getStat() == StatCode::INS);
    }

    SECTION("Get and set PC") {
        cpu.setPC(42);
        REQUIRE(cpu.getPC() == 42);

        cpu.setPC(100);
        REQUIRE(cpu.getPC() == 100);
    }
}
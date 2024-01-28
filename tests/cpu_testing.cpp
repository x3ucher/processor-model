#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>

//#include "../cpu/include/processor.hpp"
#include "../asm/include/assembler.hpp"

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

    SECTION("Execute program") {
        CPUPtr cpu_ptr = std::make_shared<CPU>(cpu);
        Assemble ass("/home/urtoach/Desktop/proc_model/tests/testdata/valid_file.txt", cpu_ptr);
        //REQUIRE_NOTHROW(ass.interpreter());
        ProgramMemory program = ass.interpreter();
        REQUIRE_NOTHROW(cpu_ptr->loadProgram(program));
        REQUIRE_NOTHROW(cpu_ptr->execute());

    }
}
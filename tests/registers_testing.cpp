#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>

#include "include/registers.hpp" 

TEST_CASE("Register: Initialization") {
    Register reg = {GPRegister::rax, 10, false};

    SECTION("Check register name") {
        REQUIRE(reg.name == GPRegister::rax);
    }

    SECTION("Check register value") {
        REQUIRE(reg.value == 10);
    }

    SECTION("Check register lock") {
        REQUIRE(reg.lock == false);
    }
}

TEST_CASE("RegisterBlock: Initialization") {
    RegisterBlock regBlock;

    SECTION("Check all registers initialized to zero") {
        for (size_t i = 0; i < NUMBER_OF_GPR; ++i) {
            REQUIRE(regBlock.getRegister(static_cast<GPRegister>(i)).value == 0);
        }
    }

    SECTION("Check all registers unlocked") {
        for (size_t i = 0; i < NUMBER_OF_GPR; ++i) {
            REQUIRE(regBlock.getRegister(static_cast<GPRegister>(i)).lock == false);
        }
    }
    
    SECTION("Check individual register value setting") {
        regBlock.setRegister(GPRegister::rax, 20);
        REQUIRE(regBlock.getRegister(GPRegister::rax).value == 20);
    }

    SECTION("Check locking/unlocking individual register") {
        regBlock.lockRegister(GPRegister::rax);
        REQUIRE(regBlock.getRegister(GPRegister::rax).lock == true);

        regBlock.unlockRegister(GPRegister::rax);
        REQUIRE(regBlock.getRegister(GPRegister::rax).lock == false);
    }

    SECTION("Check locking/unlocking all registers") {
        regBlock.lockAll();
        for (size_t i = 0; i < NUMBER_OF_GPR; ++i) {
            REQUIRE(regBlock.getRegister(static_cast<GPRegister>(i)).lock == true);
        }

        regBlock.unlockAll();
        for (size_t i = 0; i < NUMBER_OF_GPR; ++i) {
            REQUIRE(regBlock.getRegister(static_cast<GPRegister>(i)).lock == false);
        }
    }
}
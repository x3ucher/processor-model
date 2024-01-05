#define CATCH_CONFIG_MAIN 

#include <sstream>
#include <catch2/catch.hpp>

#include "myvector.hpp"

TEST_CASE("Constructor and Assignment Operator Test", "[MyVector]") {
    MyVector<int> vec1;
    REQUIRE(vec1.size() == 0);
    REQUIRE(vec1.capacity() == 0);

    MyVector<int> vec2(5);
    REQUIRE(vec2.size() == 5);
    REQUIRE(vec2.capacity() == 5);

    MyVector<int> vec3 = vec2;
    REQUIRE(vec3.size() == 5);
    REQUIRE(vec3.capacity() == 5);

    MyVector<int> vec4;
    vec4 = vec3;
    REQUIRE(vec4.size() == 5);
    REQUIRE(vec4.capacity() == 5);
}

TEST_CASE("Operator[] Test", "[MyVector]") {
    MyVector<int> vec(5);
    for (int i = 0; i < 5; ++i) {
        vec[i] = i * 2;
    }

    REQUIRE(vec[0] == 0);
    REQUIRE(vec[2] == 4);
    REQUIRE(vec[4] == 8);
}

TEST_CASE("Push_Back, Pop_Back, Size, Capacity Test", "[MyVector]") {
    MyVector<int> vec;
    REQUIRE(vec.size() == 0);
    REQUIRE(vec.capacity() == 0);

    vec.push_back(10);
    REQUIRE(vec.size() == 1);
    REQUIRE(vec.capacity() == 1);
    REQUIRE(vec[0] == 10);

    vec.pop_back();
    REQUIRE(vec.size() == 0);
    REQUIRE(vec.capacity() == 1);
}
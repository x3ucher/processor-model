#define CATCH_CONFIG_MAIN 

#include <sstream>
#include <catch2/catch.hpp>

#include "../myvector/myvector.hpp"

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

TEMPLATE_TEST_CASE("MyVector Copy Constructor", "[MyVector][Copy Constructor]", int, double, char) {
    MyVector<TestType> original;
    original.push_back(1);
    original.push_back(2);
    original.push_back(3);

    MyVector<TestType> copy(original);

    REQUIRE(copy.size() == original.size());

    for (size_t i = 0; i < original.size(); ++i) {
        REQUIRE(copy[i] == original[i]);
    }
}

TEMPLATE_TEST_CASE("MyVector Move Constructor", "[MyVector][Move Constructor]", int, double, char) {
    MyVector<TestType> original;
    original.push_back(1);
    original.push_back(2);
    original.push_back(3);

    MyVector<TestType> moved(std::move(original));

    REQUIRE(original.size() == 0);
    REQUIRE(original.capacity() == 0);
    REQUIRE(original.begin() == original.end());

    REQUIRE(moved.size() == 3);
    REQUIRE(moved.capacity() >= 3);

    REQUIRE(moved[0] == 1);
    REQUIRE(moved[1] == 2);
    REQUIRE(moved[2] == 3);
}

TEMPLATE_TEST_CASE("MyVector Copy Assignment Operator", "[MyVector][Copy Assignment]", int, double, char) {
    MyVector<TestType> original;
    original.push_back(1);
    original.push_back(2);
    original.push_back(3);
    MyVector<TestType> assigned;

    assigned = original;

    REQUIRE(assigned.size() == original.size());

    for (size_t i = 0; i < original.size(); ++i) {
        REQUIRE(assigned[i] == original[i]);
    }
}

TEMPLATE_TEST_CASE("MyVector Move Assignment Operator", "[MyVector][Move Assignment]", int, double, char) {
    MyVector<TestType> original;
    original.push_back(1);
    original.push_back(2);
    original.push_back(3);

    MyVector<TestType> assigned;
    assigned = std::move(original);

    REQUIRE(original.size() == 0);
    REQUIRE(original.capacity() == 0);
    REQUIRE(original.begin() == original.end());

    REQUIRE(assigned.size() == 3);
    REQUIRE(assigned.capacity() >= 3);

    REQUIRE(assigned[0] == 1);
    REQUIRE(assigned[1] == 2);
    REQUIRE(assigned[2] == 3);
}

TEMPLATE_TEST_CASE("MyVector Element Access Operator", "[MyVector][Element Access]", int, double, char) {
    const size_t initial_size = 3;
    MyVector<TestType> vec(initial_size);

    SECTION("Non-const version") {
        for (size_t i = 0; i < initial_size; ++i) {
            vec[i] = static_cast<TestType>(i + 1);
        }

        for (size_t i = 0; i < initial_size; ++i) {
            REQUIRE(vec[i] == static_cast<TestType>(i + 1));
        }
    }

    SECTION("Const version") {
        for (size_t i = 0; i < initial_size; ++i) {
            const TestType& value = vec[i];
            REQUIRE(value == vec[i]); 
        }
        REQUIRE_THROWS_AS(vec[initial_size], std::invalid_argument);
    }
}

TEMPLATE_TEST_CASE("MyVector Iterators", "[MyVector][Iterators]", int, double, char) {
    const size_t initial_size = 3;
    MyVector<TestType> vec(initial_size);

    SECTION("Non-const iterators") {
        auto it_begin = vec.begin();
        auto it_end = vec.end();

        REQUIRE(it_begin == vec.begin());
        REQUIRE(it_end == vec.end());
    }

    SECTION("Const iterators") {
        const MyVector<TestType>& constVec = vec; 
        auto it_cbegin = constVec.cbegin();
        auto it_cend = constVec.cend();

        REQUIRE(it_cbegin == constVec.cbegin());
        REQUIRE(it_cend == constVec.cend());
    }
}

TEMPLATE_TEST_CASE("MyVector Insert, Erase, and Emplace", "[MyVector][Insert][Erase][Emplace]", int, double, char) {
        SECTION("Insert") {
        MyVector<TestType> vec;
        vec.push_back(1);
        vec.push_back(3);

        auto it = vec.begin() + 1; 
        auto inserted_it = vec.insert(it, 2.0);

        REQUIRE(vec.size() == 3);
        REQUIRE(*inserted_it == 2.0);
        REQUIRE(vec[0] == 1);
        REQUIRE(vec[1] == 2.0);
        REQUIRE(vec[2] == 3);
    }

    SECTION("Insert Rvalue") {
        MyVector<TestType> vec;
        vec.push_back(1);
        vec.push_back(3);

        auto it = vec.begin() + 1; 
        auto inserted_it = vec.insert(it, TestType(2));

        REQUIRE(vec.size() == 3);
        REQUIRE(*inserted_it == 2);
        REQUIRE(vec[0] == 1);
        REQUIRE(vec[1] == 2);
        REQUIRE(vec[2] == 3);
    }

    SECTION("Erase") {
        MyVector<TestType> vec;
        vec.push_back(1);
        vec.push_back(2);
        vec.push_back(3);

        auto it = vec.begin() + 1; 
        auto erased_it = vec.erase(it);

        REQUIRE(vec.size() == 2);
        REQUIRE(erased_it == vec.begin() + 1);
        REQUIRE(vec[0] == 1);
        REQUIRE(vec[1] == 3);
    }

    /*
    SECTION("Emplace") {
        MyVector<TestType> vec;
        vec.emplace_back(1, 2, 3);

        REQUIRE(vec.size() == 1);
        REQUIRE(vec[0] == TestType(1, 2, 3));
    } */
}

TEST_CASE("Emplace at the beginning of the vector", "[emplace]") {
    MyVector<int> vec;
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);

    auto it = vec.begin();
    vec.emplace(it, 1);

    REQUIRE(vec.size() == 4);
    REQUIRE(vec[0] == 1);
    REQUIRE(vec[1] == 2);
    REQUIRE(vec[2] == 3);
    REQUIRE(vec[3] == 4);
}

TEST_CASE("Emplace in the middle of the vector", "[emplace]") {
    MyVector<std::string> vec;
    vec.push_back("apple");
    vec.push_back("orange");
    vec.push_back("grape");

    auto it = vec.begin() + 1;
    vec.emplace(it, "banana");

    REQUIRE(vec.size() == 4);
    REQUIRE(vec[0] == "apple");
    REQUIRE(vec[1] == "banana");
    REQUIRE(vec[2] == "orange");
    REQUIRE(vec[3] == "grape");
}

TEST_CASE("Emplace at the end of the vector", "[emplace]") {
    MyVector<double> vec;
    vec.push_back(1.1);
    vec.push_back(2.2);
    vec.push_back(3.3);

    auto it = vec.end();
    vec.emplace(it, 4.4);

    REQUIRE(vec.size() == 4);
    REQUIRE(vec[0] == 1.1);
    REQUIRE(vec[1] == 2.2);
    REQUIRE(vec[2] == 3.3);
    REQUIRE(vec[3] == 4.4);
}

TEST_CASE("Emplace with invalid iterator position", "[emplace]") {
    MyVector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    auto it = vec.end() + 1;

    REQUIRE_THROWS_AS(vec.emplace(it, 4), std::out_of_range);
    REQUIRE(vec.size() == 3);
}

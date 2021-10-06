#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "catch.hpp"

TEST_CASE("Catch operability", "[simple]"){
    REQUIRE(1+1 == 2);
}

#include "funcs.h"

TEST_CASE("test 1, file", "[simple]"){
    std::ofstream inputPrepare;
    inputPrepare.open ("input.txt", std::ofstream::trunc);
    inputPrepare<<"1\n"
                  "10 20";
    inputPrepare.close();

    std::ifstream input( "input.txt", std::ofstream::in);
    std::ofstream output("output.txt", std::ofstream::trunc);
    parseFile(input,output);
    input.close();
    output.close();
    
    std::ifstream outputCheck("output.txt", std::ofstream::in);
    std::stringstream buffer;
    buffer<<outputCheck.rdbuf();
    outputCheck.close();
    REQUIRE(buffer.str() == "10\n");
}
/*
TEST_CASE("file 017", ""){
    BENCHMARK("Can cover with 0 len"){
        std::ifstream input( "../017", std::ofstream::in);
        std::stringstream output;
        parseFile(input,output);
        input.close();
        REQUIRE(output.str() == "0\n");
    };
}
*/
TEST_CASE("test 2", ""){
    std::stringstream input, output;
    input<<"1\n"
           "10 10";
    parseFile(input,output);
    REQUIRE(output.str() == "0\n");
}

TEST_CASE("test 3", ""){
    std::stringstream input, output;
    input<<"2\n"
           "10 20\n"
           "20 40";
    parseFile(input,output);
    REQUIRE(output.str() == "30\n");
}

TEST_CASE("partially overlap", ""){
    std::stringstream input, output;
    input<<"2\n"
           "10 30\n"
           "20 40";
    parseFile(input,output);
    REQUIRE(output.str() == "30\n");
}

TEST_CASE("full overlap", ""){
    std::stringstream input, output;
    input<<"2\n"
           "10 40\n"
           "10 40";
    parseFile(input,output);
    REQUIRE(output.str() == "30\n");
}

TEST_CASE("one contains another 1", ""){
    std::stringstream input, output;
    input<<"2\n"
           "10 40\n"
           "20 40";
    parseFile(input,output);
    REQUIRE(output.str() == "30\n");
}

TEST_CASE("one contains another 2", ""){
    std::stringstream input, output;
    input<<"2\n"
           "10 40\n"
           "20 30";
    parseFile(input,output);
    REQUIRE(output.str() == "30\n");
}

TEST_CASE("one contains another 3", ""){
    std::stringstream input, output;
    input<<"2\n"
           "10 40\n"
           "10 30";
    parseFile(input,output);
    REQUIRE(output.str() == "30\n");
}

TEST_CASE("negative", ""){
    std::stringstream input, output;
    input<<"2\n"
           "-30 -10\n"
           "-40 -20";
    parseFile(input,output);
    REQUIRE(output.str() == "30\n");
}

TEST_CASE("both signs", ""){
    std::stringstream input, output;
    input<<"2\n"
           "-10 10\n"
           "-20 0";
    parseFile(input,output);
    REQUIRE(output.str() == "30\n");
}

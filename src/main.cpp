#include "ig.h"

#include <iostream>
#include <fstream>

int main() {
    IG test;

    // test for all variables AND
    // test.setVariableCount(4);
    // std::vector<unsigned> con{3, 4};
    // std::vector<bool> negate{false, false};
    // std::vector<bool> table{0,1,1,0};
    // IGNode test_node(con, negate, table);
    // test.addNode(test_node);

    // std::vector<unsigned> con1{1, 2};
    // std::vector<bool> negate1{false, false};
    // std::vector<bool> table1{0,1,1,0};
    // IGNode test_node1(con1, negate1, table1);
    // test.addNode(test_node1);

    // std::vector<unsigned> con2{5, 6};
    // std::vector<bool> negate2{false, false};
    // std::vector<bool> table2{0,1,1,0};
    // IGNode test_node2(con2, negate2, table2);
    // test.addNode(test_node2);


    // test for XOR on 2 variables
    // test.setVariableCount(2);
    // std::vector<unsigned> con{1, 2};
    // std::vector<bool> negate{true, false};
    // std::vector<bool> table{0,0,0,1};
    // IGNode test_node(con, negate, table);
    // test.addNode(test_node);

    // std::vector<unsigned> con1{1, 2};
    // std::vector<bool> negate1{false, true};
    // std::vector<bool> table1{0,0,0,1};
    // IGNode test_node1(con1, negate1, table1);
    // test.addNode(test_node1);

    // std::vector<unsigned> con2{3, 4};
    // std::vector<bool> negate2{true, true};
    // std::vector<bool> table2{0,0,0,1};
    // IGNode test_node2(con2, negate2, table2);
    // test.addNode(test_node2);

    // test.setOutput(5);
    // test.setNegateOutput(true);

    // test.print(std::cout);

    // auto f = test.getFunction();
    // f.bigPrint(std::cout);

    test.setVariableCount(2);

    std::ifstream inputFile("./src/input.txt");
    if (inputFile.is_open()) {
        test.read(inputFile);
        inputFile.close();
    } else {
        std::cout << "ERROR OPENING FILE!\n";
        return 0;
    }

    // test.read(std::cin);

    test.print(std::cout);

    auto f = test.getFunction();
    f.bigPrint(std::cout);

    return 0;
}
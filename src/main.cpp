#include "ig.h"
#include "ig_bruteforce.h"

#include <iostream>
#include <fstream>

std::ofstream file;

int main() {
    // IG test;

    // test.setVariableCount(5);

    // std::ifstream inputFile("./src/input.txt");
    // if (inputFile.is_open()) {
    //     test.read(inputFile);
    //     inputFile.close();
    // } else {
    //     std::cout << "ERROR OPENING FILE!\n";
    //     return 0;
    // }

    // test.print(std::cout);

    // auto f = test.getResult();
    // f.print(std::cout);
    // // f.bigPrint(std::cout);

    // IG test;
    // test.setVariableCount(2);
    // test.addFunction(Function({0,0,0,1}));
    // IGBruteforcer bruteforce_test;
    // bruteforce_test.bruteforce(test, 2);

    file.open("output.txt", std::ios::out);

    IG aig_test;
    aig_test.setVariableCount(4);
    aig_test.addFunction(Function({0,0,0,1}));
    IGBruteforcer bruteforce_aig_test;
    bruteforce_aig_test.bruteforce(aig_test, 5);


    // IG xaig_test;
    // xaig_test.setVariableCount(4);
    // xaig_test.addFunction(Function({0,0,0,1}));
    // xaig_test.addFunction(Function({0,1,1,0}));
    // IGBruteforcer bruteforce_xaig_test;
    // bruteforce_xaig_test.bruteforce(xaig_test, 5);


    return 0;
}

// mincode, complex, graph (MKS), 
// not found for this

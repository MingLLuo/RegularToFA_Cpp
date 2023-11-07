//
// Created by MingLLuo on 2023/10/14.
//
#include "regScanner.cpp"

void testScanner(const std::string &input) {
    std::cout << "Input: " << input << "\n";
    std::vector <Token> tokens = tokenize(input);
    tokenPrint(tokens);
    std::cout << "\n";
}

int main() {
    std::string input1 = "(a|b)*abb";
    std::string input2 = "a|b";
    std::string input3 = "(a|b)+";
    std::string input4 = "a*b";
    std::string input5 = "ab";
    std::string input6 = "a|b*";

    testScanner(input1);
    testScanner(input2);
    testScanner(input3);
    testScanner(input4);
    testScanner(input5);
    testScanner(input6);
    return 0;
}

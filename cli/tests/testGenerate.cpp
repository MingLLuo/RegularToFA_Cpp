//
// Created by MingLLuo on 2023/10/17.
//

#include "dfa.cpp"
#include "generateLexer.cpp"
#include "nfa.cpp"
#include "regExp.cpp"

int main() {
    // ((a|b)*b)*
    auto nfaConcat = stringToRegExp("((a|b)b)*")->toNFA();
    const auto &nfa = nfaConcat;
    printNFA(*nfa);
    // Convert NFA to DFA
    flush();
    auto dfa = convertToDFA(nfa);
    // Print the DFA
    dfa->printDFA();

    std::cout << "------\n";

    auto new_dfa = dfa->minimizeDFA();
    new_dfa->printDFA();
    new_dfa->acceptString("abab");
    new_dfa->acceptString("abc");
    new_dfa->acceptString("abb");
    // No need to manually delete, smart pointers handle memory cleanup

    generateLexerToFile(new_dfa, "hello.cpp");
    return 0;
}
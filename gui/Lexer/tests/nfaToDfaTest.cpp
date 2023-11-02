//
// Created by MingLLuo on 2023/10/14.
//
#include "dfa.cpp"
#include "nfa.cpp"
#include "regExp.cpp"

int main() {
    // (a|b)b?
    auto nfaConcat = stringToRegExp("(a|b)b?")->toNFA();
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
    new_dfa->acceptString("a");
    new_dfa->acceptString("ab");
    new_dfa->acceptString("bb");

    return 0;
}

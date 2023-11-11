//
// Created by MingLLuo on 2023/10/14.
//
#include "dfa.cpp"
#include "nfa.cpp"
#include "regExp.cpp"

int main() {
    // (a|b)*b?
    auto nfaConcat = stringToRegExp("((A|-)?dd*)(.dd*)?((B|e)((A|-)?dd*))?")->toNFA();
    const auto &nfa = nfaConcat;
    // Convert NFA to DFA
    flush();
    auto dfa = convertToDFA(nfa);
    // Print the DFA
//    dfa->printDFA();

    std::cout << "------\n";
    std::string testSet[] = {"d", "Ad", "-d", "ddd", "Add", "-d.dd", "--d.d", "dBAdd", "d.dB-d", "d.d--d-d"};
    for (const auto &s: testSet) {
        std::cout << "String: " << s;
        dfa->acceptString(s);
    }
    flush();
    auto new_dfa = dfa->minimizeDFA();
    new_dfa->printDFA();

    for (const auto &s: testSet) {
//        std::cout << "String: " << s << " ";
        new_dfa->acceptString(s);
    }
    // No need to manually delete, smart pointers handle memory cleanup

    return 0;
}
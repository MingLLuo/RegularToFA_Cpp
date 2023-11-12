//
// Created by MingLLuo on 2023/10/14.
//
#include "dfa.cpp"
#include "nfa.cpp"
#include "regExp.cpp"

int main() {
    auto nfaConcat = stringToRegExp("((=|-)?dd*)(.dd*)?((F|e)((=|-)?dd*))?")->toNFA();
    const auto &nfa = nfaConcat;
    // Convert NFA to DFA
    flush();
    auto dfa = convertToDFA(nfa);
    // Print the DFA
    dfa->printDFA();

    std::cout << "------\n";
    std::string testSet[] = {"dd", "=d", "-d", "--d.dd", "ddd", "=dd", "-d.dd", "--d.d", "dF=dd", "d.dF-d", "d.d--d-d"};
    for (const auto &s: testSet) {
        dfa->acceptString(s);
    }
    flush();
    auto new_dfa = dfa->minimizeDFA();
    new_dfa->printDFA();

    for (const auto &s: testSet) {
        new_dfa->acceptString(s);
    }

    return 0;
}

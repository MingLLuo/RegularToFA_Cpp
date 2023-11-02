//
// Created by MingLLuo on 2023/10/14.
//

#ifndef LEXICAL_DFA_H
#define LEXICAL_DFA_H

#include "nfa.h"
#include "util.h"
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <unordered_set>
#include <utility>
#include <vector>

class DFAState {
public:
    int id;
    std::set<std::shared_ptr<NFAState>> nfa_states;
    std::map<char, std::shared_ptr<DFAState>> transitions;
    bool is_final;

    DFAState(std::set<std::shared_ptr<NFAState>> nfa_states);

    DFAState(int id) : id(id) {}

    void printDFAState() const;

    void printTransitions() const;
};

class DFA {
public:
    std::shared_ptr<DFAState> start_state;
    std::set<std::shared_ptr<DFAState>> dfa_states;
    std::set<char> symbols;

    void printDFA() const;

    std::shared_ptr<DFA> minimizeDFA();

    void acceptString(const std::string &str) const;
};

#endif // LEXICAL_DFA_H
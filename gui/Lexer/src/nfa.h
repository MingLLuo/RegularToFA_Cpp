//
// Created by MingLLuo on 2023/10/14.
//

#ifndef LEXICAL_NFA_H
#define LEXICAL_NFA_H

#include <memory>
#include <set>
#include <unordered_map>
#include <map>
#include "util.h"

class NFAState {
public:
    int id;
    bool is_final;
    std::unordered_map<char, std::set<std::shared_ptr<NFAState>>> transitions;

    explicit NFAState(int state_id, bool final_state = false)
            : id(state_id), is_final(final_state) {}
};

class NFA {
public:
    std::set<std::shared_ptr<NFAState>> states;
    std::shared_ptr<NFAState> start_state;
    std::set<char> symbols;

    NFA();

    ~NFA() = default;

    void mergeStatesFromNFA(const std::shared_ptr<NFA> &nfa);

    void copyCleanNFA(const std::shared_ptr<NFA> &nfa, bool withFinal);

    void copySymbols(const std::shared_ptr<NFA> &nfa);
};

#endif // LEXICAL_NFA_H

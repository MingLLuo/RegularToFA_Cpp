//
// Created by MingLLuo on 2023/10/14.
//

#include "nfa.h"

NFA::NFA() : start_state(nullptr) { this->symbols.insert(0); }

void NFA::mergeStatesFromNFA(const std::shared_ptr<NFA> &nfa) {
    // move all states of nfa to this, won't copy start state

    for (const auto &state: nfa->states) {
        states.insert(state);
    }
    // copy symbol table
    copySymbols(nfa);
}

void NFA::copySymbols(const std::shared_ptr<NFA> &nfa) {
    for (auto symbol: nfa->symbols) {
        symbols.insert(symbol);
    }
}

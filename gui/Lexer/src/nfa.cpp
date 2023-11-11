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

void NFA::copyCleanNFA(const std::shared_ptr<NFA> &nfa, bool withFinal) {
    copySymbols(nfa);
    std::map<std::shared_ptr<NFAState>, std::shared_ptr<NFAState>> state_map;
    for (const auto &state: nfa->states) {
        auto new_state = std::make_shared<NFAState>(fresh());
        if (withFinal && state->is_final) {
            new_state->is_final = true;
        }
        // use old transitions first
        new_state->transitions = state->transitions;

        this->states.insert(new_state);
        state_map[state] = new_state;
    }
    for (const auto &state: this->states) {
        for (const auto &transition: state->transitions) {
            std::set<std::shared_ptr<NFAState>> new_nextStates;
            for (const auto &oldNext_state: transition.second) {
                if (state_map.find(oldNext_state) == state_map.end()) {
                    new_nextStates.insert(oldNext_state);
                } else {
                    new_nextStates.insert(state_map[oldNext_state]);
                }
            }
            state->transitions[transition.first] = new_nextStates;
        }
    }
    start_state = state_map[nfa->start_state];
}
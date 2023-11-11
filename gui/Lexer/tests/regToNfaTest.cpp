//
// Created by MingLLuo on 2023/10/14.
//

#include "nfa.cpp"
#include "regExp.cpp"
#include "util.h"
#include <iostream>

int main() {
    // Test 1: Single character regex
    auto regExpA = stringToRegExp("a");
    auto nfaA = regExpA->toNFA();
    std::cout << "NFA for 'a':\n";
    printNFA(*nfaA);
    flush();

    // Test 2: Union of characters
    auto regExpAB = stringToRegExp("a|b");
    auto nfaAB = regExpAB->toNFA();
    std::cout << "\nNFA for 'a|b':\n";
    printNFA(*nfaAB);
    flush();

    // Test 3: Concatenation of characters
    auto regExpConcat = stringToRegExp("ab");
    auto nfaConcat = regExpConcat->toNFA();
    std::cout << "\nNFA for 'ab':\n";
    printNFA(*nfaConcat);
    flush();

    // Test 4: Kleene star on a character
    auto regExpStar = stringToRegExp("a*");
    auto nfaStar = regExpStar->toNFA();
    std::cout << "\nNFA for 'a*':\n";
    printNFA(*nfaStar);
    flush();

    // Test 5: Ques on a character
    auto regExpQues = stringToRegExp("ab?");
    auto nfaQues = regExpQues->toNFA();
    std::cout << "\nNFA for 'ab?':\n";
    printNFA(*nfaQues);
    flush();

    // Test 6: Plus on two character
    auto regExpPlus = stringToRegExp("(ab)+");
    auto nfaPlus = regExpPlus->toNFA();
    std::cout << "\nNFA for '(ab)+':\n";
    printNFA(*nfaPlus);
    flush();

    // Test 7: Mult-Test
    auto regExp1 = stringToRegExp("((=|-)?dd*)(.dd*)?((F|e)((=|-)?dd*))?");
    auto nfa1 = regExp1->toNFA();
    std::cout << regExpToString(regExp1);
    std::cout << "\nNFA for ((=|-)?dd*)(.dd*)?((F|e)((=|-)?dd*))?:\n";
    printNFA(*nfa1);
    flush();

    return 0;
}

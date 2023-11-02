//
// Created by MingLLuo on 2023/10/10.
//

#ifndef LEXICAL_REGEXP_H

#include "nfa.h"
#include "regScanner.cpp"
#include "set"
#include "util.h"
#include <iostream>
#include <stack>
#include <utility>

class RegExp {
public:
    enum class Type {
        EmptyString, // Epsilon
        Char,
        Union,
        Ques,
        Concat,
        Star,
        Plus,
    };

    RegExp()
            : type(Type::EmptyString), c('\0'), left(nullptr), right(nullptr) {}

    RegExp(char ch) : type(Type::Char), c(ch), left(nullptr), right(nullptr) {}

    RegExp(Type t) : type(t), c('\0'), left(nullptr), right(nullptr) {}

    RegExp(std::shared_ptr<RegExp> l, std::shared_ptr<RegExp> r, Type t)
            : type(t), c('\0'), left(std::move(l)), right(std::move(r)) {}

    RegExp(std::shared_ptr<RegExp> r, Type t)
            : type(t), c('\0'), left(nullptr), right(std::move(r)) {}

    // Destructor
    ~RegExp() = default;

    [[nodiscard]] std::shared_ptr<NFA> toNFA() const;

    Type type;
    char c;
    std::shared_ptr<RegExp> left;
    std::shared_ptr<RegExp> right;
};

#endif // LEXICAL_REGEXP_H

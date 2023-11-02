//
// Created by MingLLuo on 2023/10/14.
//

#ifndef LEXICAL_UTIL_H
#define LEXICAL_UTIL_H
int fresh_counter = 0;

int fresh() { return ++fresh_counter; }

void flush() { fresh_counter = 0; }

#endif // LEXICAL_UTIL_H

#include "dfa.h"
#include <fstream>
#include <iostream>
#include <sstream>

std::string generateLexer(const std::shared_ptr<DFA> &dfa) {
    std::ostringstream code;

    code << "#include <iostream>\n";
    code << "#include <string>\n\n";

    for (const auto &state: dfa->dfa_states) {
        code << "void state" << state->id
             << "(char inputSymbol, int& currentState) {\n";
        for (const auto &transition: state->transitions) {
            if (transition.first != 0 && transition.second != nullptr) {
                code << "    if (inputSymbol == '" << transition.first
                     << "') {\n";
                code << "        currentState = " << transition.second->id
                     << ";\n";
                code << "        return;\n";
                code << "    }\n";
            }
        }
        code << "    currentState = -1; // Invalid transition\n";
        code << "}\n\n";
    }

    code << "bool acceptInput(const std::string& input) {\n";
    code << "    int currentState = " << dfa->start_state->id << ";\n";
    code << "    for (char inputSymbol : input) {\n";
    code << "        switch (currentState) {\n";

    for (const auto &state: dfa->dfa_states) {
        code << "            case " << state->id << ":\n";
        code << "                state" << state->id
             << "(inputSymbol, currentState);\n";
        code << "                break;\n";
    }

    code << "            default:\n";
    code << "                return false;\n";
    code << "        }\n";
    code << "        if (currentState == -1)\n";
    code << "            return false;\n";
    code << "    }\n\n";
    for (const auto &state: dfa->dfa_states) {
        if (state->is_final) {
            code << "    if (currentState == " << state->id << ")\n";
            code << "        return true;\n";
        }
    }
    code << "    return false;\n";
    code << "}\n\n";
    code << "int main() {\n";
    code << "    std::string input;\n";
    code << "    std::cout << \"Enter input symbols: \";\n";
    code << "    std::cin >> input;\n";
    code << "    bool accepted = acceptInput(input);\n";
    code << "    std::cout << \"Input is \" << (accepted ? \"accepted\" : "
            "\"rejected\") << std::endl;\n";
    code << "    return 0;\n";
    code << "}\n";

    return code.str();
}

void generateLexerToFile(const std::shared_ptr<DFA> &dfa,
                         const std::string &filename) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file for writing: " << filename
                  << std::endl;
        return;
    }

    file << generateLexer(dfa);

    file.close();
}

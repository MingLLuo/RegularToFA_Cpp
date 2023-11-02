#include <iostream>
#include <string>

void state7(char inputSymbol, int& currentState) {
    if (inputSymbol == 'b') {
        currentState = 9;
        return;
    }
    currentState = -1; // Invalid transition
}

void state8(char inputSymbol, int& currentState) {
    if (inputSymbol == 'a') {
        currentState = 7;
        return;
    }
    if (inputSymbol == 'b') {
        currentState = 7;
        return;
    }
    currentState = -1; // Invalid transition
}

void state9(char inputSymbol, int& currentState) {
    if (inputSymbol == 'a') {
        currentState = 7;
        return;
    }
    if (inputSymbol == 'b') {
        currentState = 7;
        return;
    }
    currentState = -1; // Invalid transition
}

bool acceptInput(const std::string& input) {
    int currentState = 9;
    for (char inputSymbol : input) {
        switch (currentState) {
            case 7:
                state7(inputSymbol, currentState);
                break;
            case 8:
                state8(inputSymbol, currentState);
                break;
            case 9:
                state9(inputSymbol, currentState);
                break;
            default:
                return false;
        }
        if (currentState == -1)
            return false;
    }

    return currentState == 9;
}

int main() {
    std::string input;
    std::cout << "Enter input symbols: ";
    std::cin >> input;
    bool accepted = acceptInput(input);
    std::cout << "Input is " << (accepted ? "accepted" : "rejected") << std::endl;
    return 0;
}

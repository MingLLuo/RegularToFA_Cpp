#include <iostream>
#include <string>

void state5(char inputSymbol, int &currentState) {
    if (inputSymbol == 'b') {
        currentState = 6;
        return;
    }
    currentState = -1; // Invalid transition
}

void state6(char inputSymbol, int &currentState) {
    if (inputSymbol == 'a') {
        currentState = 5;
        return;
    }
    if (inputSymbol == 'b') {
        currentState = 5;
        return;
    }
    currentState = -1; // Invalid transition
}

bool acceptInput(const std::string &input) {
    int currentState = 6;
    for (char inputSymbol: input) {
        switch (currentState) {
            case 5:
                state5(inputSymbol, currentState);
                break;
            case 6:
                state6(inputSymbol, currentState);
                break;
            default:
                return false;
        }
        if (currentState == -1)
            return false;
    }

    return currentState == 6;
}

int main() {
    std::string input;
    std::cout << "Enter input symbols: ";
    std::cin >> input;
    bool accepted = acceptInput(input);
    std::cout << "Input is " << (accepted ? "accepted" : "rejected")
              << std::endl;
    return 0;
}

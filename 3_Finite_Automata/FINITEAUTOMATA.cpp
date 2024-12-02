#include "FINITEAUTOMATA.h"
#include <sstream>
#include <iostream>
#include <unordered_set>
using namespace std;

void FiniteAutomata::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    cout << filename;
    std::string line;
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    std::cout << "File " << filename << " opened successfully.\n";

    std::getline(file, line);
    std::cout << line << std::endl;
    parseStates(line);

    std::getline(file, line);
    parseAlphabet(line);
    std::cout << line << std::endl;

    std::getline(file, line);
    initialState = parseInitialState(line);
    std::cout << line << std::endl;

    std::getline(file, line);
    parseFinalStates(line);
    std::cout << line << std::endl;

    std::getline(file, line);
    std::cout << line << std::endl;
    while (std::getline(file, line)) {
        parseTransition(line);
    }

    checkDeterminism();
}

void FiniteAutomata::displayMenu() {
    int choice;
    do {
        std::cout << "menu:\n";
        std::cout << "1 -> display all states\n";
        std::cout << "2 -> display the alphabet\n";
        std::cout << "3 -> display the transitions\n";
        std::cout << "4 -> display initial state\n";
        std::cout << "5 -> display final states\n";
        std::cout << "0 -> exit\n";
        std::cout << "enter your choice -> ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
        case 1:
            displayStates();
            break;
        case 2:
            displayAlphabet();
            break;
        case 3:
            displayTransitions();
            break;
        case 4:
            displayInitialState();
            break;
        case 5:
            displayFinalStates();
            break;
        case 0:
            std::cout << "exiting\n";
            break;
        default:
            std::cout << "invalid choice! try again.\n";
        }
    } while (choice != 0);
}

void FiniteAutomata::parseStates(const std::string& line) {
    std::istringstream stream(line); 
    std::string state;
    while (stream >> state) {  
        states.insert(state);
    }
}

void FiniteAutomata::parseAlphabet(const std::string& line) {
    std::istringstream stream(line);
    char symbol;
    while (stream >> symbol) {
        alphabet.insert(symbol);
    }
}

std::string FiniteAutomata::parseInitialState(const std::string& line) {
    return line.substr(line.find(":") + 1);  
}

void FiniteAutomata::parseFinalStates(const std::string& line) {
    std::istringstream stream(line);
    std::string state;
    while (stream >> state) {
        finalStates.insert(state);
    }
}



void FiniteAutomata::checkDeterminism() {
    for (const auto& [state, transitionsForState] : transitions) {
        for (const auto& [symbol, toState] : transitionsForState) {
            if (transitionsForState.count(symbol) > 1) {
                std::cerr << "nondeterministic transition detected for state "
                    << state << " and symbol " << symbol << ".\n";
            }
        }
    }
    std::cout << "The FA is deterministic.\n";
}



void FiniteAutomata::parseTransition(const std::string& line) {
    std::istringstream stream(line);
    std::string from, to;
    char symbol;
    stream >> from >> symbol >> to;
    if (transitions[from].find(symbol) != transitions[from].end()) {
        std::cerr << "nondeterministic transition detected for state " << from
            << " and symbol " << symbol << ".\n";
    }

    transitions[from][symbol] = to;
}

void FiniteAutomata::displayStates() {
    std::cout << "states: ";
    for (const auto& state : states) {
        std::cout << state << " ";
    }
    std::cout << "\n";
}

void FiniteAutomata::displayAlphabet() {
    std::cout << "alphabet: ";
    for (const auto& symbol : alphabet) {
        std::cout << symbol << " ";
    }
    std::cout << "\n";
}

void FiniteAutomata::displayTransitions() {
    std::cout << "transitions:\n";
    for (const auto& stateTransitions : transitions) {
        for (const auto& transition : stateTransitions.second) {
            std::cout << stateTransitions.first << " --" << transition.first << "--> " << transition.second << "\n";
        }
    }
}

void FiniteAutomata::displayInitialState() {
    std::cout << "initial State: " << initialState << "\n";
}

void FiniteAutomata::displayFinalStates() {
    std::cout << "final States: ";
    for (const auto& state : finalStates) {
        std::cout << state << " ";
    }
    std::cout << "\n";
}



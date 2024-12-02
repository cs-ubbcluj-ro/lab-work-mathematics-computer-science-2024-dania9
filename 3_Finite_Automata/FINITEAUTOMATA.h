#pragma once
#ifndef FINITEAUTOMATA_H
#define FINITEAUTOMATA_H

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <set>
#include <string>

class FiniteAutomata {
public:
    std::set<std::string> states;
    std::set<char> alphabet;
    std::string initialState;
    std::set<std::string> finalStates;
    std::unordered_map<std::string, std::unordered_map<char, std::string>> transitions;


    void loadFromFile(const std::string& filename);
    void displayMenu();

private:
    void parseStates(const std::string& line);
    void parseAlphabet(const std::string& line);
    std::string parseInitialState(const std::string& line);
    void parseFinalStates(const std::string& line);
    void parseTransition(const std::string& line);
    void checkDeterminism();
    void displayStates();
    void displayAlphabet();
    void displayTransitions();
    void displayInitialState();
    void displayFinalStates();
    void verifySequence();
};




#endif 

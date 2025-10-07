#ifndef IMPROVED_DICTIONARY_H
#define IMPROVED_DICTIONARY_H

#include "Dictionary.h"
#include <map>
#include <string>
#include <vector>

using namespace std;

class ImprovedDictionary : public Dictionary
{
private:
    map<std::string, map<char, int>> charProbabilities;  // Map to store probabilities

    void calculateCharProbabilities(const string& filename);  // Function to calculate probabilities from text

    vector<char> getTopThreeChars(const string& twoChars) const;  // Function to get top three likely characters

    string generateWord() const;   // Function to generate a single word

public: 
    ImprovedDictionary(); // Constructor
    void generateParagraph(); // Method to generate a paragraph
    void getLikelyChars(); // Method to get likely characters for two-character input
    void menu() override; // Override menu to include new options
};
#endif
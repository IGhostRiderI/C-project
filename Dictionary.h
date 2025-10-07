#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <vector>
#include <string>
#include "Word.h"

using namespace std;

class Dictionary {
private:
    vector<Word> words;  // Vector to store Word objects

    string getTypeAbbreviation(const string& type) const;

protected:
    const vector<Word>& getWords() const { return words; }

public:
    Dictionary();  // Constructor

    void getDictionary(const string& dictionary); // Method to load dictionary from file
    void searchWord() const;  // Method to search a word
    void randomWord() ;  // Method to display a random word
    virtual void menu();  // Method to display and handle the menu
};

#endif

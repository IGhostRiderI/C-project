#ifndef WORD_H
#define WORD_H

#include <string>
using namespace std;

class Word {
private:
    string name;
    string type;
    string definition;

public:
    // Constructor
    Word(const string& name, const string& type, const string& definition);

    // Default Constructor
    Word();

    // Getters
    string getName() const;
    string getType() const;
    string getDefinition() const;

    // Setters
    void setName(const string& name);
    void setType(const string& type);
    void setDefinition(const string& definition);

    // Print definition function
    void printDefinition() const;
};

#endif
#include "Word.h"
#include <iostream>

// Constructor implementations
Word::Word(const string& name, const string& type, const string& definition)    
    : name(name), type(type), definition(definition) {
}

Word::Word() : name(""), type(""), definition("") {}


// Getter implementations
string Word::getName() const {   
    return name;
}

string Word::getType() const {
    return type;
}

string Word::getDefinition() const {
    return definition;
}


// Setter implementations
void Word::setName(const string& name) {
    this->name = name;
}

void Word::setType(const string& type) {
    this->type = type;
}

void Word::setDefinition(const string& definition) {
    this->definition = definition;
}

// function = printDefinition
// created by = Maleesha Perera
// date created = 19/05/2025
// purpose = To print the word, type and definition in a formatted manner
// input = none
// output = prints the word, type and definition
void Word::printDefinition() const {
    string formattedType;

    if (type == "prep") formattedType = "(prep)";
    else if (type == "n_and_v") formattedType = "(n. v.)";
    else formattedType = " (" + type + ".) ";

    cout << "Name: " << name << "\nType: " << formattedType << "\nDefinition:\n*" << definition << endl;
}

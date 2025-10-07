#include "Dictionary.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <random> 
#include <chrono> 

using namespace std;

Dictionary::Dictionary() {}   // Default constructor for the Dictionary class

string Dictionary::getTypeAbbreviation( const string& type) const 
{
    if (type == "prep") return "(prep)";
    else if (type == "n_and_v") return "(n. v.)";
    else return " (" + type + ".) ";
}
// function = getDictionary
// created by = Maleesha Perera
// date created = 19/05/2025
// purpose = To load the dictionary from a text file and store the words in a vector of Word objects
// input = dictionary file name
// output = error message if file not found, else prints the number of words loaded
void Dictionary::getDictionary(const string& dictionary)
{ 
     cout << "Loading dictionary...\n\n";
     ifstream dictionaryFile(dictionary);
       
    // Check if file opened successfully
    if (!dictionaryFile)
    {     
        cout << "Unable to load the dictionary" << endl;
        return;
    }
    string firstline, name, type, definition;

    getline(dictionaryFile, firstline); // To read the first line in the dictionary txt file

    while (getline(dictionaryFile, name)) // To read the dictionary file line by line and process
    {         
        if (name.empty()) continue;    // To skip blank lines

        getline(dictionaryFile, type);
        getline(dictionaryFile, definition);

        if (!name.empty() && name.back() == ';') name.pop_back();    // To remove tailing ";" in the name and type
        if (!type.empty() && type.back() == ';') type.pop_back();

        int l = definition.length();

        for (int i = 0; i < l; i++)
        {
            // check for ";" in definition and replace with \n to start multiple definitions in new lines
            if (definition[i] == ';')
            {
                definition[i] = '\n';
                i++;
                definition[i] = '*';
            }
        }
        words.emplace_back(name, type, definition);   // Add the new Word object to the vector
    }

    dictionaryFile.close();
    cout << "Dictionary successfully loaded with " << words.size() << " words\n";
}

// function = searchWord
// created by = Maleesha Perera
// date created = 19/05/2025
// purpose = To search for a word in the dictionary and print its definition
// input = none
// output = Prints the type and definition of the search word, else prints an error message
void Dictionary::searchWord() const 
{
    if (words.empty())   // Checks if the dictionary is empty
    {
        cout << "Error - dictionary empty\n";
        return;
    }

    string searchingWord;
    cout << "Enter a word to search: ";
    cin >> searchingWord;    // get the word from user to search
    cout << endl;

    transform(searchingWord.begin(), searchingWord.end(), searchingWord.begin(), ::tolower);    // Convert user input to lowercase

    for (const auto& word : words)  // To loop through the vector
    {
        if (word.getName() == searchingWord)
        {
            word.printDefinition();
            return;
        }
    }
    cout << "Word not found\n";
}

// function = randomWord
// created by = Maleesha Perera
// date created = 19/05/2025
// purpose = To get a random word from the dictionary and print its type and definition
// input = none
// output = Prints the type and definition of the random word, else prints an error message
void Dictionary::randomWord()
{
    if (words.empty())
    {
        cout << "No words loaded in the dictionary.\n";
        return;
    }
    // Use a static random number generator, seeded once
    static mt19937 rng(static_cast<unsigned>(chrono::high_resolution_clock::now().time_since_epoch().count()));
    uniform_int_distribution<int> dist(0, words.size() - 1);

    int randomIndex = dist(rng);
    cout << "Random Word: " << words[randomIndex].getName() << endl;
    cout << "Type: " << words[randomIndex].getType() << endl;
    cout << "Definition: \n* " << words[randomIndex].getDefinition() << endl;
}

// function = menu
// created by = Maleesha Perera
// date created = 19/05/2025
// purpose = To display the menu and get user input
// input = User choice(string)
// output = error message if invalid input
void Dictionary::menu() 
{
    string choice;

    while (choice != "4") 
    {
        Sleep(1000);  // Add a Delay
        cout << "\nDictionary Menu:\n";   //prints the options
        cout << "1. Load dictionary\n";
        cout << "2. Search for a word\n";
        cout << "3. Get a random word\n";
        cout << "4. Exit\n\n";
        cout << "Enter choice: ";
        cin >> choice;       //Get user choice
        cout << endl;

        if (choice == "1") {getDictionary("dictionary_2025S1.txt");}
        else if (choice == "2") { searchWord();}
        else if (choice == "3") {randomWord();}
        else if (choice == "4") {cout << "Exiting program...\n";}
        else {cout << "Invalid input, try again\n";}
    }
}

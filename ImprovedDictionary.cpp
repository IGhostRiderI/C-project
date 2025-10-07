#include "ImprovedDictionary.h"
#include <iostream> 
#include <fstream> 
#include <algorithm> 
#include <cstdlib> 
#include <ctime> 
#include <windows.h> 

using namespace std; 

// Constructor implementation
ImprovedDictionary::ImprovedDictionary() 
{ 
    srand(static_cast<unsigned int>(time(0))); // Seeds the random number generator
}

// function calculateCharProbabilities
// author = Maleesha Perera
// date created = 20/05/2025 
// purpose = Counts how often each character follows a two-character sequence in the file
// inputs = The dictionary file "dictionary_2025S1.txt".
// outputs = display success message or error message
void ImprovedDictionary::calculateCharProbabilities(const string& filename) 
{
    charProbabilities.clear(); // Empty the map so we start fresh
    ifstream file(filename); 

    if (!file)
    { // Check if we couldn't open the file
        cout << "Error: Unable to open file " << filename << endl;
        return; 
    }

    string line; 
    cout << "\nCalculating probabilities, please wait...\n"; 
    while (getline(file, line)) // Read the file line by line
    { 
        if (line.length() < 3) continue; // Skip lines that are too short (need at least 3 chars)
        
        for (size_t i = 0; i < line.length() - 2; ++i)
        {
            string twoChars = line.substr(i, 2); // Get two characters starting at position i
            char nextChar = line[i + 2]; // Get the character that comes after those two
            charProbabilities[twoChars][nextChar]++;
        }
    }
    cout << "\nSuccessfully calculated probabilities\n"; 
    file.close(); 
}

// function getTopThreeChars
// author = Maleesha Perera
// date created = 20/05/2025
// purpose = Get the top three most likely characters to follow a two-character sequence
// inputs = twoChars(string) 
// outputs = A vector of up to three characters, else shows an error message
vector<char> ImprovedDictionary::getTopThreeChars(const string& twoChars) const
{   
    vector<char> result; // This will hold the top three characters
    auto it = charProbabilities.find(twoChars); // Look for the two-character sequence

	if (it == charProbabilities.end())  // Check if probabilities exist for this sequence
    { 
        cout << "No data for sequence: " << twoChars << endl;
        return result; 
    }
    vector<pair<char, int>> charCounts(it->second.begin(), it->second.end()); // Copy the counts into a vector 
    sort(charCounts.begin(), charCounts.end(),
        [](const pair<char, int>& a, const pair<char, int>& b) {
            return b.second < a.second; // Sort from highest count to lowest
        });

    for (size_t i = 0; i < min<size_t>(3, charCounts.size()); ++i)  // Add up to three characters to the result
    {  
        result.push_back(charCounts[i].first); 
    }
    return result; 
}

// function = generateWord
// created by = Maleesha Perera
// date created = 21/05/2025
// purpose = Creates a made-up word by using the character probabilities
// inputs = None 
// outputs = Word(string), else shows an error message
string ImprovedDictionary::generateWord() const 
{
    if (charProbabilities.empty())  // Checks if we have any probabilities
    {  
        return "No probabilities available"; 
    }
    vector<string> keys;

    for (const auto& pair : charProbabilities)  // Get all the known two-character sequences 
    {  
        keys.push_back(pair.first); // Add each two-character sequence to the list
    }
    string current = keys[rand() % keys.size()]; // Pick a random starting sequence
    string word = current; // Start the word with those two characters
    
	int wordLength = 3 + (rand() % 8); // Get random word length between 3 and 10 characters

    while ((int)word.length() < wordLength)   // Keep adding characters until we reach the length
    { 
        vector<char> nextChars = getTopThreeChars(current); // Get the likely next characters
		if (nextChars.empty()) break; 
        char nextChar = nextChars[rand() % nextChars.size()];  // Pick one of the top three characters randomly
        word += nextChar; 
        current = current.substr(1) + nextChar;     
    }
    return word; 
}

// function = generateParagraph
// created by = Maleesha Perera
// date created = 21/05/2025
// purpose = Creates a paragraph of 4-8 sentences, each with 5-10 made-up words
// inputs = None
// outputs = print the generated paragraph, else shows an error message
void ImprovedDictionary::generateParagraph()
{   
    if (charProbabilities.empty())  // Checks if we have any probabilities
    {  
        cout << "Error, dictionary is not loaded\n";
        return; 
    }

    int numSentences = 4 + (rand() % 5);  // To get random number of sentences between 4 to 8

    for (int i = 0; i < numSentences; ++i)  // Loop to create each sentence
    {   
        int numWords = 5 + (rand() % 6);  // To get random number of words between 5 to 10
        for (int j = 0; j < numWords; ++j)  // Loop to create each word in the sentence
        { 
            cout << generateWord();  
            if (j < numWords - 1) cout << " "; // Add a space between words
			else cout << ". ";    //  Add a period at the end of the sentence
        }
        if (i < numSentences - 1) cout << "\n"; // Add a new line between sentences
    }
    cout << endl; 
}

// function = getLikelyChars
// created by = Maleesha Perera
// date created = 21/05/2025
// purpose = Lets the user enter a two character and shows the most likely next characters
// inputs = User input of two characters(string) 
// outputs = Prints the most likely next characters, else shows an error message
void ImprovedDictionary::getLikelyChars() 
{
    if (charProbabilities.empty())  // Checks if we have any probabilities
    {  
        cout << "Please load the dictionary first to calculate probabilities.\n";
        return; 
    }
    string twoChars; 
    cout << "Enter two characters: "; 
    cin >> twoChars; 

    if (twoChars.length() != 2)  // Make sure user entered exactly two characters
    { 
        cout << "Please enter exactly two characters.\n";
        return; 
    }
    vector<char> likelyChars = getTopThreeChars(twoChars); // Find the likely characters

	if (likelyChars.empty())  // Check if there is any data for this sequence
    { 
        cout << "No likely characters found for sequence: " << twoChars << endl;
    }
    else
    { 
        cout << "Most likely characters after \"" << twoChars << "\": ";
		for (char c : likelyChars)
        {   // To loop through each character and print it
            cout << "\n* " << c ;
        }
        cout << endl; 
    }
}

// function = menu
// created by = Maleesha Perera
// date created = 21/05/2025
// purpose = Shows a menu with options to load the dictionary
// inputs = User input of choice(string) 
// outputs = Calls the appropriate function based on user input, else shows an error message
void ImprovedDictionary::menu() 
{   
    string choice; 
    while (choice != "6")   // Keep showing the menu until the user picks 6 to exit
    {  
        Sleep(1000); // 1 secong delay
        cout << "\nImproved Dictionary Menu:\n"; // Shows the menu options
        cout << "1. Load dictionary\n"; 
        cout << "2. Search for a word\n"; 
        cout << "3. Get a random word\n"; 
        cout << "4. Get likely characters\n"; 
        cout << "5. Generate paragraph\n"; 
        cout << "6. Exit\n\n"; 
        cout << "Enter choice: "; 
        cin >> choice; 
        cout << endl; 

        if (choice == "1")    // Load the appropriate fution based on user input
        {    
			getDictionary("dictionary_2025S1.txt"); 
            calculateCharProbabilities("dictionary_2025S1.txt"); 
        }
        else if (choice == "2") { searchWord(); } 
        else if (choice == "3") { randomWord(); } 
        else if (choice == "4") { getLikelyChars(); } 
        else if (choice == "5") { generateParagraph(); } 
        else if (choice == "6") { cout << "Exiting program...\n"; } 
        else { cout << "Invalid input, try again\n"; } 
    }
}
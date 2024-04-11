#include "TimeInterval.h"
#include <iostream>
#include <fstream>
#include <unordered_set>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// Convert to lowercase for case-insensitive comparison
string toLowerCase(const string& str) {
    string lowerCaseStr = str;
    transform(lowerCaseStr.begin(), lowerCaseStr.end(), lowerCaseStr.begin(), ::tolower);
    return lowerCaseStr;
}

// Check if word is in dictionary
bool isWordInDictionary(const unordered_set<string>& dict, const string& word) {
    return dict.find(toLowerCase(word)) != dict.end();
}

// Simple similarity measure based on matching characters
int wordSimilarity(const string& word1, const string& word2) {
    int minLength = min(word1.length(), word2.length());
    int similarity = 0;
    for (int i = 0; i < minLength; ++i) {
        if (word1[i] == word2[i]) {
            similarity++;
        }
    }
    return similarity;
}

// Suggest the most similar word in the dictionary
string suggestSimilarWord(const unordered_set<string>& dict, const string& word) {
    string suggestedWord = "";
    int maxSimilarity = 0;

    for (const string& dictWord : dict) {
        int similarity = wordSimilarity(word, dictWord);
        if (similarity > maxSimilarity) {
            maxSimilarity = similarity;
            suggestedWord = dictWord;
        }
    }

    return suggestedWord;
}

// Get suggestions starting with the same first two letters
vector<string> getSuggestions(const unordered_set<string>& dict, const string& firstTwoLetters) {
    vector<string> suggestions;
    for (const string& w : dict) {
        if (w.substr(0, 2) == firstTwoLetters) {
            suggestions.push_back(w);
        }
    }
    return suggestions;
}

int main() {
    TimeInterval timer;
    // string filename = "/Users/yaochen/CLionProjects/PA6/Dictionary.txt";
    string filename = "Dictionary.txt";
    ifstream inFile(filename);
    string line;
    unordered_set<string> dictionary;

    if (!inFile.is_open()) {
        cout << "Error opening file " << filename << endl;
        return 1;
    }

    while (getline(inFile, line)) {
        dictionary.insert(toLowerCase(line));
    }
    inFile.close();

    cout << "Please enter a word: ";
    string userWord;
    cin >> userWord;

    timer.start();
    string lowerUserWord = toLowerCase(userWord);

    if (isWordInDictionary(dictionary, lowerUserWord)) {
        cout << "True\n";
        auto suggestions = getSuggestions(dictionary, lowerUserWord.substr(0, 2));
        for (const auto& s : suggestions) {
            cout << s << endl;
        }
    } else {
        string suggestedWord = suggestSimilarWord(dictionary, lowerUserWord);
        if (!suggestedWord.empty()) {
            cout << "Do you mean " << suggestedWord << "? (yes/no): ";
            string response;
            cin >> response;
            if (response == "yes") {
                cout << "True\n";
                auto suggestions = getSuggestions(dictionary, suggestedWord.substr(0, 2));
                for (const auto& s : suggestions) {
                    cout << s << endl;
                }
            } else {
                cout << "False\n";
            }
        } else {
            cout << "False\n";
        }
    }

    timer.stop();
    cout << "Execution time: " << timer.GetInterval() << " micro-sec\n";
    return 0;
}

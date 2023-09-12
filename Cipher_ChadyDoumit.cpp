// Chady Doumit
// 7/23/2023
// Cipher Project

// This program decrypts a text that has a cipher encryption by trying out 
// all shifts and comparing the words to the 100 most common english words.

#include <iostream>
#include <fstream>
#include <string>
#include <cctype> // for isspace and ispunct

using namespace std;

//Compares word to 100 most common english words
bool isList(string word) {
    //Creating Array containing 100 most common words in English
    string words[100] = {
        "the", "of", "and", "a", "to", "in", "is", "you", "that", "it",
            "he", "was", "for", "on", "are", "as", "with", "his", "they", "I",
            "at", "be", "this", "have", "from", "or", "one", "had", "by", "word",
            "but", "not", "what", "all", "were", "we", "when", "your", "can", "said",
            "there", "use", "an", "each", "which", "she", "do", "how", "their", "if",
            "will", "up", "other", "about", "out", "many", "then", "them", "these", "so",
            "some", "her", "would", "make", "like", "him", "into", "time", "has", "look",
            "two", "more", "write", "go", "see", "number", "no", "way", "could", "people",
            "my", "than", "first", "water", "been", "call", "who", "oil", "its", "now",
            "find", "long", "down", "day", "did", "get", "come", "made", "may", "part"
    };
    for (int i = 0; i < 100; i++) {
        if (word == words[i]) {
            //cout << endl << words[i] << endl;
            return true;
        }
    }

    return false;
}

char caesarDecryptSingle(char ch, int shift) {
    if (isupper(ch))
        return ((ch - 'A' - shift + 26) % 26) + 'A';  // '+26' is to handle negative numbers
    else if (islower(ch))
        return ((ch - 'a' - shift + 26) % 26) + 'a';  // '+26' is to handle negative numbers
    else
        return ch;  // do not change punctuation or whitespace
}

// Function to decrypt the text
string decrypt(const string& text, int shift) {
    string result;
    for (char ch : text) {
        result += caesarDecryptSingle(ch, shift);
    }
    return result;
}



int main()
{
    //Creating Text Variables
    ifstream CipherText;
    ofstream SolvedText;

    //Opening and Creating Files
    CipherText.open("cipher.txt");
    SolvedText.open("SolvedCipher.txt");
    //Counts Matches per try
    int MatchAmount[25];

    //Cipher Shift Solved
    int SolvedShift = 0;

    for (int i = 0; i < 25; i++) {
        MatchAmount[i] = 0;
    }
    string tempstr = "";
    string TextIn = "";
    string tempword = "";


    while (getline(CipherText, tempstr)) {
        TextIn += tempstr; // append each line to the string
    }

    //Checks Every word in every shift and compares it to top 100 words
    //Amount of Matches are noted in MatchAmount for every shift
    for (int shift = 1; shift <= 25; shift++) {
        string TextOut = decrypt(TextIn, shift);

        for (int i = 1; i < (TextOut.size() - 1); i++) {
            if (!isspace(TextOut[i]) && !ispunct(TextOut[i])) {
                tempword += TextOut[i];
            }
            else {
                if (isList(tempword)) {
                    MatchAmount[shift-1]++;
                }
                tempword = "";
                
            }
        }        
    }


    //Determines which shift had the highest amount of matches
    int BiggestMatch = 0;
    for (int i = 0; i < 25; i++) {
        if (MatchAmount[i] > BiggestMatch) {
            SolvedShift = i + 1;
            BiggestMatch = MatchAmount[i];
        }
    }
    

    //Displaying Ciphered Text
    cout << "Ciphered Text: " << endl << endl;
    cout << TextIn << endl << endl;

    //Decrypt cipher using correct shift
    string TextOut = decrypt(TextIn, SolvedShift);

    //Displaying Solved cipher number
    cout << endl << endl << "Cipher Shift " << SolvedShift << endl;

    //Displaying Solved Text
    cout << endl << "Solved Text : " << endl << endl;
    
    cout << TextOut<<endl;

    CipherText.close();
    SolvedText.close();
}


#include <iostream>
#include <unordered_map>
#include <string>
#include <cstdlib>

using namespace std;

unordered_map<char, string> morseCodeMap = {
    {'a', ".-"}, {'b', "-..."}, {'c', "-.-."}, {'d', "-.."},
    {'e', "."}, {'f', "..-."}, {'g', "--."}, {'h', "...."},
    {'i', ".."}, {'j', ".---"}, {'k', "-.-"}, {'l', ".-.."},
    {'m', "--"}, {'n', "-."}, {'o', "---"}, {'p', ".--."},
    {'q', "--.-"}, {'r', ".-."}, {'s', "..."}, {'t', "-"},
    {'u', "..-"}, {'v', "...-"}, {'w', ".--"}, {'x', "-..-"},
    {'y', "-.--"}, {'z', "--.."},
    {'0', "-----"}, {'1', ".----"}, {'2', "..---"}, {'3', "...--"},
    {'4', "....-"}, {'5', "....."}, {'6', "-...."}, {'7', "--..."},
    {'8', "---.."}, {'9', "----."}
};

unordered_map<string, char> reverseMorseCodeMap;

void initializeReverseMap() {
    for (const auto& pair : morseCodeMap) {
        reverseMorseCodeMap[pair.second] = pair.first;
    }
}

string morseEncode(char x) {
    if (isalpha(x))
        x = tolower(x);

    if (morseCodeMap.find(x) != morseCodeMap.end()) {
        return morseCodeMap[x];
    } else {
        cerr << "Invalid character: " << x << endl;
        exit(EXIT_FAILURE);
    }
}

string encrypt(const string& text) {
    string encryptedText = "";
    for (char c : text) {
        if (c == ' ') {
            encryptedText += " ";
        } else {
            encryptedText += morseEncode(c) + " ";
        }
    }
    return encryptedText;
}

string decrypt(const string& cipherText) {
    string decryptedText = "";
    string morseCode = "";
    for (char c : cipherText) {
        if (c == ' ') {
            if (reverseMorseCodeMap.find(morseCode) != reverseMorseCodeMap.end()) {
                decryptedText += reverseMorseCodeMap[morseCode];
            }
            morseCode = "";
        } else {
            morseCode += c;
        }
    }
    if (reverseMorseCodeMap.find(morseCode) != reverseMorseCodeMap.end()) {
        decryptedText += reverseMorseCodeMap[morseCode];
    }
    return decryptedText;
}

int main() {
    initializeReverseMap();

    char choice;
    string text, result;

    cout << "Enter 'e' to encrypt or 'd' to decrypt: ";
    cin >> choice;

    if (choice == 'e') {
        cout << "Enter the plain text: ";
        cin.ignore(); // Clear input buffer
        getline(cin, text);
        result = encrypt(text);
        cout << "Encrypted text: " << result << endl;
    } else if (choice == 'd') {
        cout << "Enter the cipher text: ";
        cin.ignore(); // Clear input buffer
        getline(cin, text);
        result = decrypt(text);
        cout << "Decrypted text: " << result << endl;
    } else {
        cout << "Invalid choice. Please enter 'e' or 'd'." << endl;
    }

    return 0;
}

#include <iostream>
#include <map>
#include <istream>
#include <string>
using namespace std;

std::string encrypt(const std::string& plaintext) {
    std::map<char, int> charToIndex;
    std::map<int, char> indexToChar;
    char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (int i = 0; i < 26; ++i) {
        charToIndex[alphabet[i]] = i;
        indexToChar[i] = alphabet[i];
    }

    std::string ciphertext;
    for (char ch : plaintext) {
        if (isalpha(ch)) {
            char encryptedChar = indexToChar[(charToIndex[toupper(ch)] + 3) % 26];
            ciphertext += islower(ch) ? tolower(encryptedChar) : encryptedChar;
        } else {
            ciphertext += ch;
        }
    }

    return ciphertext;
}

std::string decrypt(const std::string& ciphertext) {
    std::map<char, int> charToIndex;
    std::map<int, char> indexToChar;
    char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (int i = 0; i < 26; ++i) {
        charToIndex[alphabet[i]] = i;
        indexToChar[i] = alphabet[i];
    }

    std::string decryptedText;
    for (char ch : ciphertext) {
        if (isalpha(ch)) {
            char decryptedChar = indexToChar[(charToIndex[toupper(ch)] + 23) % 26];
            decryptedText += islower(ch) ? tolower(decryptedChar) : decryptedChar;
        } else {
            decryptedText += ch;
        }
    }

    return decryptedText;
}

int main() {
    string input;
    cout << "Enter text to encrypt: ";
    std::getline(std::cin, input);
    //std::cin.ignore(); 

    string encrypted = encrypt(input);
    string decrypted = decrypt(encrypted);

    cout << "Encrypted: " << encrypted << std::endl;
    std::cout << "Decrypted: " << decrypted << std::endl;

    return 0;
}

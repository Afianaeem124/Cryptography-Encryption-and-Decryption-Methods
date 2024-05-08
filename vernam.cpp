#include <iostream>
#include <string>

using namespace std;

// Function to perform XOR operation on a character and a key byte
char xor_char(char a, char b) {
  return a ^ b;
}

// Function to encrypt the plain text using Vernam Cipher
string encryptVernam(string plainText, string key) {
  string cipherText;

  // Ensure key length is at least as long as the plain text
  if (key.length() < plainText.length()) {
    key.append(plainText.length() - key.length(), key[0]); // Repeat first key byte
  }

  for (int i = 0; i < plainText.length(); i++) {
    cipherText.push_back(xor_char(plainText[i], key[i]));
  }

  return cipherText;
}

// Function to decrypt the cipher text using Vernam Cipher
string decryptVernam(string cipherText, string key) {
  string plainText;

  // Ensure key length is at least as long as the cipher text
  if (key.length() < cipherText.length()) {
    key.append(cipherText.length() - key.length(), key[0]); // Repeat first key byte
  }

  for (int i = 0; i < cipherText.length(); i++) {
    plainText.push_back(xor_char(cipherText[i], key[i]));
  }

  return plainText;
}

int main() {
  int choice;
  string text, key;

  cout << "Enter 1 for Encryption or 2 for Decryption: ";
  cin >> choice;

  if (choice == 1) {
    cout << "Enter the text to encrypt: ";
    cin.ignore(); // Consume newline character
    getline(cin, text);

    cout << "Enter the key for encryption: ";
    getline(cin, key);

    string cipherText = encryptVernam(text, key);
    cout << "Encrypted Text: " << cipherText << endl;
  } else if (choice == 2) {
    cout << "Enter the text to decrypt: ";
    cin.ignore(); // Consume newline character
    getline(cin, text);

    cout << "Enter the key for decryption: ";
    getline(cin, key);

    string plainText = decryptVernam(text, key);
    cout << "Decrypted Text: " << plainText << endl;
  } else {
    cout << "Invalid choice. Please enter 1 for encryption or 2 for decryption." << endl;
  }

  return 0;
}

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Function to generate the key in a cyclic manner until its length isn't equal to the length of the original text
string generateKey(string str, string key) {
    int x = str.size();

    for (int i = 0; ; i++) {
        if (x == i)
            i = 0;
        if (key.size() == str.size())
            break;
        key.push_back(key[i]);
    }
    return key;
}

// Function to encrypt the text using Vigenère cipher with mathematical calculation
string encrypt(string plaintext, string key) {
    string ciphertext;

    for (int i = 0; i < plaintext.size(); i++) {
        char x = (plaintext[i] + key[i]) % 26; // converting in range 0-25
        x += 'A'; // convert into alphabets(ASCII)
        ciphertext.push_back(x);
    }
    return ciphertext;
}

// Function to decrypt the text using Vigenère cipher with mathematical calculation
string decrypt(string ciphertext, string key) {
    string decryptedtext;

    for (int i = 0; i < ciphertext.size(); i++) {
        char x = (ciphertext[i] - key[i] + 26) % 26; // converting in range 0-25
        x += 'A'; // convert into alphabets(ASCII)
        decryptedtext.push_back(x);
    }
    return decryptedtext;
}

// Function to encrypt the text using Vigenère cipher with table method
string encryptWithTable(string plaintext, string key) {
    string ciphertext;
    vector<vector<char>> table(26, vector<char>(26));

    // Populate the table
    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < 26; ++j) {
            table[i][j] = (char)((i + j) % 26 + 'A');
        }
    }

    // Encrypt the plaintext using the table
    for (int i = 0; i < plaintext.size(); ++i) {
        ciphertext += table[plaintext[i] - 'A'][key[i % key.length()] - 'A'];
    }

    return ciphertext;
}

// Driver program to test the functions
int main() {
    string plaintext = "AFIANAEEM";
    string keyword = "LOCK";

    string key = generateKey(plaintext, keyword);
    string cipher_text = encrypt(plaintext, key);
    string decrypted_text = decrypt(cipher_text, key);

    cout << "Ciphertext (Mathematical Calculation): " << cipher_text << "\n";
    cout << "Decrypted Text (Mathematical Calculation): " << decrypted_text << "\n";

    // Encrypt and Decrypt using Table method
    string cipher_text_table = encryptWithTable(plaintext, key);
    string decrypted_text_table = decrypt(cipher_text_table, key);

    cout << "Ciphertext (Table Method): " << cipher_text_table << "\n";
    cout << "Decrypted Text (Table Method): " << decrypted_text_table << "\n";

    return 0;
}

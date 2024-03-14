#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int SIZE = 5;

class PlayfairCipher {
private:
    char matrix[SIZE][SIZE];

    void generateMatrix(const string& key) {
        string keyWithoutDuplicates = "";
        bool present[26] = {false};

        // Construct the key without duplicate letters
        for (char c : key) {
            if (c == 'j') continue; // treat 'i' and 'j' as same
            if (!present[c - 'a']) {
                keyWithoutDuplicates += c;
                present[c - 'a'] = true;
            }
        }

        // Fill the matrix with the key
        int index = 0;
        for (char c : keyWithoutDuplicates) {
            matrix[index / SIZE][index % SIZE] = c;
            index++;
        }

        // Fill the rest of the matrix with remaining letters
        for (char c = 'a'; c <= 'z'; ++c) {
            if (c == 'j') continue; // treat 'i' and 'j' as same
            if (!present[c - 'a']) {
                matrix[index / SIZE][index % SIZE] = c;
                index++;
            }
        }
    }

    void prepareInput(string& input) {
        for (int i = 0; i < input.length(); ++i) {
            if (input[i] == 'j') input[i] = 'i'; // treat 'i' and 'j' as same
            if (isalpha(input[i]))
                input[i] = tolower(input[i]); // convert to lowercase
            else
                input.erase(i, 1); // remove non-alphabetic characters
        }
    }

    string encryptDigraph(char a, char b) {
        int row1, col1, row2, col2;

        // Find the positions of characters in the matrix
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (matrix[i][j] == a) {
                    row1 = i;
                    col1 = j;
                }
                if (matrix[i][j] == b) {
                    row2 = i;
                    col2 = j;
                }
            }
        }

        // Apply the Playfair rules
        if (row1 == row2) {
            return string(1, matrix[row1][(col1 + 1) % SIZE]) + matrix[row2][(col2 + 1) % SIZE];
        } else if (col1 == col2) {
            return string(1, matrix[(row1 + 1) % SIZE][col1]) + matrix[(row2 + 1) % SIZE][col2];
        } else {
            return string(1, matrix[row1][col2]) + matrix[row2][col1];
        }
    }

public:
    PlayfairCipher(const string& key) {
        generateMatrix(key);
    }

    string encrypt(const string& plainText) {
        string text = plainText;
        prepareInput(text);

        // Apply the Playfair cipher
        string cipherText = "";
        for (int i = 0; i < text.length(); i += 2) {
            cipherText += encryptDigraph(text[i], text[i + 1]);
        }

        return cipherText;
    }

    string decrypt(const string& cipherText) {
        // Apply the reverse of the Playfair cipher for decryption
        string plainText = "";
        for (int i = 0; i < cipherText.length(); i += 2) {
            char a = cipherText[i];
            char b = cipherText[i + 1];
            int row1, col1, row2, col2;

            // Find the positions of characters in the matrix
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < SIZE; ++k) {
                    if (matrix[j][k] == a) {
                        row1 = j;
                        col1 = k;
                    }
                    if (matrix[j][k] == b) {
                        row2 = j;
                        col2 = k;
                    }
                }
            }

            // Apply the reverse of Playfair rules
            if (row1 == row2) {
                plainText += string(1, matrix[row1][(col1 - 1 + SIZE) % SIZE]) + matrix[row2][(col2 - 1 + SIZE) % SIZE];
            } else if (col1 == col2) {
                plainText += string(1, matrix[(row1 - 1 + SIZE) % SIZE][col1]) + matrix[(row2 - 1 + SIZE) % SIZE][col2];
            } else {
                plainText += string(1, matrix[row1][col2]) + matrix[row2][col1];
            }
        }

        return plainText;
    }
};

int main() {
    string key, text;
    cout << "Enter the key: ";
    cin >> key;

    PlayfairCipher cipher(key);

    cout << "Enter the text to encrypt: ";
    cin.ignore(); // clear buffer
    getline(cin, text);
    string encryptedText = cipher.encrypt(text);
    cout << "Encrypted text: " << encryptedText << endl;

    cout << "Enter the text to decrypt: ";
    getline(cin, text);
    string decryptedText = cipher.decrypt(text);
    cout << "Decrypted text: " << decryptedText << endl;

    return 0;
}

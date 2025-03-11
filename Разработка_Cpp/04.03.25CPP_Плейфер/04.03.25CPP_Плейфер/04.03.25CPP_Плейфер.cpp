#include <iostream>
#include <string>
#include <vector>
using namespace std;

string new_alfavit(const string& slov_us)
{
    string al, al_slov;

    for (char i : slov_us)
        if (i != 'j' && al_slov.find(i) == string::npos)
            al_slov += i;

    for (int i = 97; i <= 122; i++)
    {
        char current_char = char(i);
        if (current_char != 'j' && al_slov.find(current_char) == string::npos)
            al.push_back(current_char);
    }

    al = al_slov + al;
    return al;
}

vector<vector<char>> create_matrix(const string& key) 
{
    vector<vector<char>> matrix(5, vector<char>(5));
    string alphabet = new_alfavit(key);
    int k = 0;
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j)
            matrix[i][j] = alphabet[k++];
    return matrix;
}

pair<int, int> find_char(const vector<vector<char>>& matrix, char c) 
{
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j)
            if (matrix[i][j] == c)
                return { i, j };
    return { -1, -1 };
}

string playfair_encrypt(const string& text, const string& key) 
{
    string ciphertext = "";
    vector<vector<char>> matrix = create_matrix(key);
    string prepared_text = "";
    for (char c : text)
        if (isalpha(c))
            prepared_text += tolower(c);

    if (prepared_text.length() % 2 != 0)
        prepared_text += 'x';

    for (size_t i = 0; i < prepared_text.length(); i += 2) 
    {
        char char1 = prepared_text[i];
        char char2 = prepared_text[i + 1];

        auto pos1 = find_char(matrix, char1);
        auto pos2 = find_char(matrix, char2);

        int row1 = pos1.first;
        int col1 = pos1.second;
        int row2 = pos2.first;
        int col2 = pos2.second;

        if (row1 == row2) 
        {
            ciphertext += matrix[row1][(col1 + 1) % 5];
            ciphertext += matrix[row2][(col2 + 1) % 5];
        }
        else if (col1 == col2) 
        {
            ciphertext += matrix[(row1 + 1) % 5][col1];
            ciphertext += matrix[(row2 + 1) % 5][col2];
        }
        else 
        {
            ciphertext += matrix[row1][col2];
            ciphertext += matrix[row2][col1];
        }
    }
    return ciphertext;
}

int main() 
{
    string key, plaintext;
    cout << "Key: ";
    cin >> key;
    cout << "Plaintext: ";
    cin >> plaintext;

    cout << "result: " << playfair_encrypt(plaintext, key) << endl;
}
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>
#include <memory>

using namespace std;

unique_ptr<vector<string>> file_read(const string& fname)
{
    auto uni_ptr = make_unique<vector<string>>();
    ifstream file(fname);
    if (!file.is_open())
        cout << "Error: file can't open." << endl;
    string line;
    while (getline(file, line))
        uni_ptr->push_back(line);
    return uni_ptr;
}

int count_words(const string& line)
{
    int* count = (int*)malloc(sizeof(int));
    *count = 0;
    bool in_word = false;
    for (char i : line)
    {
        if (isspace(i))
            in_word = false;
        else if (!in_word)
        {
            in_word = true;
            (*count)++;
        }
    }
    int result = *count;
    free(count);
    return result;
}

string find_longest_word(const string& line)
{
    string longest;
    size_t pos = 0, end;
    while ((end = line.find_first_of(' ', pos)) != string::npos)
    {
        string word = line.substr(pos, end - pos);
        if (word.length() > longest.length())
            longest = word;
        pos = end + 1;
    }
    string word = line.substr(pos);
    if (word.length() > longest.length())
        longest = word;
    return longest;
}

string replace_vowels(const string& line)
{
    string result = line;
    for (char& ch : result)
        if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' ||
            ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U')
                ch = '*';
    return result;
}

void write_results(const string& fname, const unique_ptr<vector<string>>& lines)
{
    ofstream outfile(fname);
    if (!outfile.is_open())
        cout << "Error: unable to open output file." << endl;

    for (const auto& line : *lines)
{
        int word_count = count_words(line);
        string longest_word = find_longest_word(line);
        string modified_line = replace_vowels(line);
        outfile << "Original: " << line << "\n"
            << "Word count: " << word_count << "\n"
            << "Longest word: " << longest_word << "\n"
            << "Modified: " << modified_line << "\n\n";
    }
}

int main()
{
    string fname = "file_meow.txt";
    string out_fname = "output_results.txt";
    auto lines = file_read(fname);
    if (lines)
        write_results(out_fname, lines);
}

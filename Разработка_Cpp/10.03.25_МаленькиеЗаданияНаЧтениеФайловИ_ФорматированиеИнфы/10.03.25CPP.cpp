#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void chunked(const string& filen, int n)
{
    ifstream file(filen);
    if (!file.is_open())
        cout << "Error opening file." << endl;

    string line, spisok;
    while (getline(file, line))
    {
        for (char i : line)
        {
            if (i == ' ')
                continue;
            else
                spisok += i;
        }
        int number_N = 1, count = 1;

        cout << '[';
        for (char i : spisok)
        {
            if (number_N < n)
            {
                if (number_N == 1)
                    cout << "['" << i << "',";
                else
                    cout << "'" << i << "',";
                number_N++; count++;
            }
            else
            {
                if (count == spisok.size())
                    cout << "'" << i << "']";
                else
                    cout << "'" << i << "'],";
                number_N = 1; count++;
            }
        }
        cout << ']';
    }
}

void file_read(const string& filen) 
{
    ifstream file(filen);
    if (!file.is_open())
        cout << "Error opening file." << endl;

    string target = "anton", line;
    int line_count = 0;

    while (getline(file, line)) 
    {
        int targetIndex = 0;
        for (char c : line) 
            if (c == target[targetIndex]) 
            {
                targetIndex++;
                if (targetIndex == target.length()) {
                    cout << line_count;
                    break;
                }
            }
        line_count++;
    }
    file.close();
}

int main() 
{
    /*string file_name = "holodos.txt";
    file_read(file_name);*/

    string file_name2 = "chunks.txt"; int n = 3;
    chunked(file_name2, n);
}

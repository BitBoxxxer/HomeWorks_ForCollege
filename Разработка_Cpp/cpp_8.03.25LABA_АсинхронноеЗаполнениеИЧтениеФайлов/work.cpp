#include "Header.h"
#include <algorithm>
#include <iostream>

void wrt_file(const string& fname, int count, mutex& mtx) 
{
    ofstream f(fname);
    if (!f.is_open()) 
    {
        cout << "Файл не открывается:(1) " << fname << endl;
        return;
    }

    for (int i = 0; i < count; i++)
    {
        lock_guard<mutex> lock(mtx);
        int random_number = rand() % 100;
        f << random_number << endl;
        cout << "Записано в [" << fname << "]: " << random_number << endl;
        this_thread::sleep_for(chrono::milliseconds(5));
    }
    f.close();
}

vector<int> read_file(const string& fname)
{
    vector<int> num_from_file;
    ifstream f(fname);
    int number = 0;
    while (f >> number)
        num_from_file.push_back(number);
    f.close();
    return num_from_file;
}

double sred_arif(const vector<int>& vec_name)
{
    if (vec_name.empty()) return 0.0;
    int sum = 0;
    for (auto i : vec_name)
        sum += i;
    return static_cast<double>(sum) / vec_name.size();
}

double mediana(vector<int>& vec_name)
{
    if (vec_name.empty()) return 0.0;
    sort(vec_name.begin(), vec_name.end());
    size_t size = vec_name.size();
    if (size % 2 == 0)
        return (vec_name[size / 2 - 1] + vec_name[size / 2]) / 2.0;
    else
        return vec_name[size / 2];
}

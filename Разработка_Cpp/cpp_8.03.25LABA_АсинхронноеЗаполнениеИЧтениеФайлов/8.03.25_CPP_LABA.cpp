#include <iostream>
#include <future>
#include <fstream>
#include <mutex>
#include <thread>
#include <vector>
#include <set>
#include <ctime>
#include "Header.h"

using namespace std;

mutex mtx;

int main() 
{
    setlocale(LC_ALL, "Russian");
    srand(time(0));

    vector<string> file_list{ "file1.txt", "file2.txt", "file3.txt" };

    for (auto& filename : file_list) {
        ofstream f(filename);
        f.close();
    }

    vector<future<void>> write_futures;
    for (const auto& filename : file_list)
        write_futures.push_back(async(launch::async, wrt_file, filename, 10, ref(mtx)));

    for (auto& fut : write_futures) // замена mutex
        fut.get();

    auto read_and_compute_average = async(launch::async, [](const vector<string>& files) {
        vector<int> all_numbers;
        for (const auto& file : files) {
            auto numbers = read_file(file);
            all_numbers.insert(all_numbers.end(), numbers.begin(), numbers.end());
        }
        return sred_arif(all_numbers);
        }, file_list);

    auto read_and_compute_median = async(launch::async, [](const vector<string>& files) {
        vector<int> all_numbers;
        for (const auto& file : files) {
            auto numbers = read_file(file);
            all_numbers.insert(all_numbers.end(), numbers.begin(), numbers.end());
        }
        return mediana(all_numbers);
        }, file_list);

    double average = read_and_compute_average.get();
    double median = read_and_compute_median.get();

    cout << "\nСреднее арифметическое: " << average << endl;
    cout << "Медиана: " << median << endl;
}

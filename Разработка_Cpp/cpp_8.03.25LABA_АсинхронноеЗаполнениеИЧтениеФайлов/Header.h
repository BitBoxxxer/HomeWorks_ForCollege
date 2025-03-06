#include <iostream>
#include <future>
#include <fstream>
#include <mutex>
#include <thread>
#include <vector>
#include <set>

using namespace std;

vector<int> read_file(const string& fname);
void wrt_file(const string& fname, int count, mutex& mtx);
double sred_arif(const vector<int>& vec_name);
double mediana(vector<int>& vec_name);

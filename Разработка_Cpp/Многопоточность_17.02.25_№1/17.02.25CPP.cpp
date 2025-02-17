#include <iostream>
#include <thread>
#include <vector>
#include <numeric>
using namespace std;

void f(vector<int>& num, int start, int end, int& res)
{
	res = accumulate(num.begin() + start, num.begin() + end, 0);
}

int main()
{
	srand(time(0));
	vector<int> num;
	for (int i = 0; i < 100; i++)
		num.push_back(rand());
	vector<int> sum(4, 0);
	vector<thread> thr;
	int n = thread::hardware_concurrency();
	int start = 0, end = 0;
	for (int i = 0; i < n; i++)
	{
		start = i * 25;
		end = start + 25;
		thr.emplace_back(f, ref(num), start, end, ref(sum[i]));

		/*thr.emplace_back(f, i);
		this_thread::sleep_for(chrono::milliseconds(10));*/
	}
	for (auto& i : thr)
		i.join();

	cout << accumulate(num.begin(), num.end(), 0);
}

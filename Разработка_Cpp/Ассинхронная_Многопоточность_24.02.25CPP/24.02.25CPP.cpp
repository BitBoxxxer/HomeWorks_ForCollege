// 24.02.25CPP.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <future>
#include <thread>
using namespace std;

int f(int &max)
{
	/*this_thread::sleep_for(chrono::seconds(5));
	return 10;*/


}

void g(int min[], promise<int> prms)
{
	/*this_thread::sleep_for(chrono::seconds(1));
	return 1000;*/
	prms.set_value(3);

	int min_result = 0;

	this_thread::sleep_for(chrono::milliseconds(5));
	for(int i = 0; i < 5; i++)
		if (min_result < min[i])
			min_result = min[i];
	cout << "Min: " << min_result << endl;
}

// ассинхронные операции, для выполнения паралельных задач.
int main()
{
	int a[5] {1,2,3,4,5};
	//thread t_max(f, a);
	thread t_min(g, a);

	//t_max.join();
	t_min.join();


	//cout << task.get() << endl; // выводит только с .get();
	//cout << task_g.get();
}

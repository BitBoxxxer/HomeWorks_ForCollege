#include <iostream>
#include <thread>
//#include <atomic> // атомарные операции [фиксация на операции, блокировка иных потоков]
#include <mutex>
#include <vector>
#include <condition_variable>
#include <semaphore>
using namespace std;

atomic <int> c = 0;
condition_variable cv;
int finish = 0;
mutex mtx;
counting_semaphore<1> semaphore(1);

void f(int i)
{
	semaphore.acquire();
	this_thread::sleep_for(chrono::seconds(2)); // тайминг для синхронизации времени
	cout << "Now run thread " << i << endl;
	semaphore.release();

	/*// синтаксис: cv.wait(lock,[],{return (bool условие);} // только bool условие
	unique_lock<mutex>lock(mtx);
	cv.wait(lock, [] { return finish; });
	cout << "Thread run.\n";
	lock.unlock();*/


	/*for (int i = 0; i < 100; i++) // пример работы atomic
		++c;
	cout << c << endl;*/
}

int main()
{
	thread t1(f, 1);
	thread t2(f, 2);
	t1.join(); t2.join();

	/*vector <thread> vec;
	for (int i = 0; i <= thread::hardware_concurrency(); i++)
	{

		if (i == 2)
			finish = true;
		else
			finish = false;

		vec.emplace_back(f);
		this_thread::sleep_for(chrono::milliseconds(1000));
		{
			lock_guard<mutex>lock(mtx);
		}
		cv.notify_one();
	}
	for (auto& i : vec)
		i.join();*/

}

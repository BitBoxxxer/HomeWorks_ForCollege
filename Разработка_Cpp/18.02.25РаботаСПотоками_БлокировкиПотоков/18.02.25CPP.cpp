#include <iostream>
#include <thread>
#include <vector>
#include <mutex> // синхронизация потоков (для тогго чтобы не было утечки потоков)
#include <queue>
#include <condition_variable> // оповещение потоков о выполнении работы других потоков

// пример: задача с потоками, где один поток добавляет элемент в очередь, второй поток их удаляет.

using namespace std;
mutex mtx;
queue <int> q;
condition_variable cv;
bool finish = false;

void f() // добавляет в очередь.
{
	for (int i = 0; i < 100; i++)
	{
		this_thread::sleep_for(chrono::milliseconds(100));
		unique_lock<mutex>lock(mtx);
		q.push(i);

		cout << "Puxh " << i << endl;
		lock.unlock();
		cv.notify_one(); // condition_variable cv;
	}
	unique_lock<mutex>lock(mtx);
	finish = true;
	cv.notify_one();
	lock.unlock(); // но т.к. фунция заканчивается, она автоматом выполняет разблокировку, так что писать unlock
	// в конце не обязательно.
}

void g()
{
	while (true)
	{
		unique_lock<mutex>lock(mtx);
		cv.wait(lock, [] {return (finish || !q.empty());}); //  [] {return (finish || !q.empty()); - проверка на bool
		if (q.empty() and finish)
			break;
		if (!q.empty())
		{
			int a = q.front();
			q.pop();
			cout << "Delete " << a << endl;
		}
		lock.unlock();
	}
}

//void f() // пример 3-х блокировок потоков, дает 1-цу времени на один поток
//{
//	for (int i = 0; i < 100; i++)
//	{
//		unique_lock<mutex>lock(mtx); // 1
//		a++;
//		lock.unlock();
//
//		//lock_guard<mutex>lock(mtx); // 2
//		
//		//mtx.lock(); // 1-ца времени на один поток. // 3
//		//a++;
//		//mtx.unlock(); // 1-ца времени на один поток.
//	}
//}

int main()
{
	thread f1(f);
	thread g1(g);
	f1.join();
	g1.join();


	/*vector<thread> thr;
	for (int i = 0; i < 100; i++)
	{
		thr.emplace_back(f);
	}
	for (auto& i : thr)
		i.join();*/
}


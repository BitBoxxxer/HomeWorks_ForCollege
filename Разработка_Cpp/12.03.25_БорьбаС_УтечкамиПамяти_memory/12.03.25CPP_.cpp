#include <iostream>
#include <memory> // new. unique
using namespace std;

/*int main()
{
	unique_ptr<int> o_ptr{};
	int ind = 0;
	for (int i = 2; i < 8000; i++)
	{
		int k = 0;
		for (int j = 2; j < i / 2; j++)
			if (i % j == 0)
				k++;
		if ((k == 3))
			ms_ptr[ind++] = i;
	}
	cout << o_ptr;
}*/

/*int main()
{
	int * p_int = new int();
	unique_ptr<int> p_ptr{p_int};

	cout << "Input number for p_ptr: ";
	cin >> *p_int;
	cout << "\nPolychil: " << *p_int;

	cout << "\np_ptr:";
}*/

/*
// борьба с утечками памяти: умный указатель.
int main()
{
	int* ptr = new int(), * ptr2 = new int(); ptr = ptr2;

	unique_ptr<int> o{new int(5)}; // ...<int> o{Можно передать тут ему значение.};
	unique_ptr<int> o2{ new int(15) };
	// компактное рамположение указателей, что ускоряет работу

	unique_ptr<int[]> ms_ptr{ make_unique<int[]>(10) }; // make_unique авто-инициализация. 
	//т.е. не нужно ставить * чтобы указать не на муссорный адресс переменной.
	for (int i = 0; i < 10; i++)
	{
		ms_ptr[i] = i * 2;
		cout << ms_ptr[i] << ' ';
	}
}*/

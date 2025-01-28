#include <iostream>
using namespace std;

void print(int* a, int n)
{
	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
}

int* f(int* a, int n)
{
	int* p = a;
	int count = 0;
	for (int i = 0; i < n; i++)
	{
		if (*a >= 0)
			count++;
		a++;
	}
	int* b = new int[count];

	int ind = 0;
	a = p;
	for (int i = 0; i < n; i++)
	{
		if (*a >= 0)
		{
			b[ind] = *a;
			ind++;
		}
		a++;
	}

	return b;
}

int main()
{
	int n = 0;
	cin >> n;
	int* a = new int[n];
	srand(time(0));
	for (int i = 0; i < n; i++)
	{
		a[i] = rand() % 100 - 50;
	}
	print(a, n);
	cout << "\n";

	int* result = f(a, n);

	int count = 0;

	for (int i = 0; i < n; i++)
	{
		if (a[i] >= 0)
			count++;
	}

	print(result, count);
}
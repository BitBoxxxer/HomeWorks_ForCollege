#include <iostream>
using namespace std;

// Theme lesson: УКАЗАТЕЛИ НА ФУНКЦИИ
int f(int n, int m, int c)
{
	cout << "Discr:" << ((m * m) - 4 * n * c) << endl;
	return (m*m)-4*n*c;
}

int Gromp (int (*function)(int, int, int), int a, int b, int c, int i)
{
	return (-b + (i * function(a, b, c))) / (2 * a);
}

int main()
{
	//ПРИНЦИП НАПИСАНИЯ: 
	// ТИП (имя_Указателя)(Аргументы){имя_Функции}
	int a = 5;
	int b = 9;
	int c = 1;

	/*int(*fun[3])(int, int) = { f,f2,f3 };
	for (int i = 0; i < 3; i++)
		fun[i](a, b);*/
	int x1 = Gromp(f, a, b, c, 1);
	cout << "First x:" << x1<<endl;
	int x2 = Gromp(f, a, b, c, -1);
	cout << "Second x:" << x2 << endl;

	/*int (*fun)(int)(f);
	cout << fun(a);*/
}

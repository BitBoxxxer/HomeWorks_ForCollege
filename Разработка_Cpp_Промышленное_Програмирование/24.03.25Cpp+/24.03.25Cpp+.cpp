#include <iostream>
using namespace std; // структуры.

struct Point
{
	int x, y, z, w;
	// создание конструктора:
	// Point () {}
	/*Point(int x, int y) { this->x = 0; this->y = y; }*/

	int Super_x = this->x + this->z; int Super_y = this->y + this->w;
	void prnt()
	{
		cout << this->x << ' ' << this->y << endl;
	}

	int Pifagor()
	{
		return sqrt((this->x * this->x) + (this->y * this->y));
	}
	int NaitiDveDots()
	{
		return sqrt((this->Super_x * this->Super_x) + (this->Super_y * this->Super_y));
	}
};

struct Point_first_square
{
private:
	int x, y;
public:
	Point_first_square(int a=0, int b=0)
	{
		if (a >= 0)
			this->x = a;
		else
		{
			cout << "err404 -> x"; return;
		}

		if (b > 0)
			this->y = b;
		else
		{
			cout << "err404 -> y"; return;
		}

		prnt();
	}

	Point_first_square() 
	{ this->x = 0; this->y = 0; prnt(); }

	void prnt()
	{ cout << this->x << ' ' << this->y << endl; }

	~Point_first_square() // деструктор работает в стеке ( удаляет объекты в обратном порядке. )
	{ cout << "Point delete"; }
};



int main()
{
	/*Point a{5,3};
	a.x = 7;
	cout << a.x << " " << a.y;*/

	/*Point dots[5] = { {1,2}, {3,4}, {4,5}, {5,6}, {8,9} };
	for (int i = 0; i < 4; i++)
		cout << dots[i].Pifagor();*/

	/*Point dotess[4] = { {1,2,3,4}, {2,3,4,5}, {3,4,5,6}, {4,5,6,7} };
	for (int i = 0; i < 4; i++)
		cout << abs(dotess[i].NaitiDveDots() - dotess[i+1].NaitiDveDots())  << endl;*/

	Point_first_square a(1, 3);
	Point_first_square c();
}

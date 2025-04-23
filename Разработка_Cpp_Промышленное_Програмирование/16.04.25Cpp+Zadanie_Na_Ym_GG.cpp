#include <iostream>
using namespace std;


class BaseC {
protected:
	int x, y;
public:
	BaseC(int x_a, int y_a) :x(x_a),y(y_a) {}

	virtual int Ploshad_S() = 0;
	virtual int Perimetr_P() = 0;
};

class Pramoygolnik : public BaseC {
public:
	Pramoygolnik(int x_a, int y_a) : BaseC(x_a, y_a) {
		cout << "\nПрямоульник: " << endl;
		cout << "S: " << Ploshad_S() << endl;
		cout << "P: " << Perimetr_P() << endl;
	}

	int Ploshad_S() override {
		return x * y;
	}
	int Perimetr_P() override {
		return 2 * x + 2 * y;
	}
};

class Kryg : public BaseC {
	int r;
public:
	Kryg(int x_a, int y_a, int r_a) : BaseC(x_a, y_a), r(r_a) {
		cout << "\nКруг: " << endl;
		cout << "S: " << Ploshad_S() << endl;
		cout << "P: " << Perimetr_P() << endl;
	}

	int Ploshad_S() override {
		return 3.14 * pow(r, 2);
	}
	int Perimetr_P() override {
		return 2 * 3.14 * r;
	}
};

class PrTreygol : public BaseC {
	double z;
public:
	PrTreygol(int x_a, int y_a) : BaseC(x_a, y_a) {
		cout << "\nПрямоугольный треугольник: " << endl;
		z = sqrt(pow(x_a, 2) + pow(y_a, 2));
		cout << "Гипотенуза трегольника: " << z << endl;
		cout << "S: " << Ploshad_S() << endl;
		cout << "P: " << Perimetr_P() << endl;
	}

	int Ploshad_S() override {
		return (x * y) / 2;
	}
	int Perimetr_P() override {
		return x + y + z;
	}
};

class Trapeci : public BaseC {
	double z, d, h;
public:
	Trapeci(int x_a, int y_a, double z, double d) : BaseC(x_a, y_a), z(z), d(d) {
		cout << "\nТрапеция: " << endl;
		int i = abs(x - y);
		h = sqrt(pow(d, 2) - pow((i / 2), 2));
		cout << "Высота трапеции: " << h << endl;
		cout << "S: " << Ploshad_S() << endl;
		cout << "P: " << Perimetr_P() << endl;
	}

	int Ploshad_S() override {
		return ((x + y) / 2) * h;
	}
	int Perimetr_P() override {
		return x + y + z + d;
	}
};

int main()
{
	setlocale(LC_ALL, "");
	int n, m, r, z, d;
	cout << "Введите ширину: "; cin >> n;
	cout << "Введите длину: "; cin >> m;
	Pramoygolnik p(n, m);
	cout << "Введите радиус круга: "; cin >> r;
	Kryg k(n,m,r);
	PrTreygol PT(n, m);
	cout << "Введите 3-ю сторону: "; cin >> z;
	cout << "Введите 4-ю сторону: "; cin >> d;
	Trapeci T(n, m, z, d);
}

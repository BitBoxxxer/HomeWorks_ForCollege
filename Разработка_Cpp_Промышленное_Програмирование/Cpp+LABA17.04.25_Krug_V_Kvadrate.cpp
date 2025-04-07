#include <iostream>
using namespace std;


class Kvadrat {
protected:
	int kv_storona;

public:
	Kvadrat() { kv_storona = 2; }

	Kvadrat(int st) {
		kv_storona = st;
	}

	int KV_V() {
		return pow(kv_storona, 2);
	}

	int Input_KV() { // сторона квадрата
		return kv_storona;
	}
};

class Circel {
protected:
	int radius_c;

public:
	Circel() { radius_c = 1; }

	Circel(int st) {
		radius_c = st;
	}

	int Circ_P() { // тоже для длины
		return 2 * 3.14 * radius_c;
	}

	int Circ_V() {
		return 3.14 * pow(radius_c, 2);
	}

	int Input_KV() { // радиус круга
		return radius_c;
	}
};

class Proverka : public Kvadrat, public Circel {
protected:
	bool in_kv = false;

public:
	Proverka(int kv_st, int cir_rad) :
		Circel(cir_rad), Kvadrat(kv_st)
	{
		if (cir_rad * 2 <= kv_st) { in_kv = true; }
		if (in_kv) {
			cout << "Сторона квадрата: " << kv_st << endl << "Объем квадрата: " << KV_V() << endl;
			cout << "Радиус окружности: " << cir_rad << endl;
			cout << "Объем круга: " << Circ_V() << endl << "Периметр круга(тоже самое что и длина): " << Circ_P() << endl;
			cout << "Статус вмещения круга в квадрат: " << in_kv << " - [1 - true, 0 - false]" << endl;
			cout << "Оставшийся объем Квадрата вне окружности: " << KV_V() - Circ_V() << endl;
		}
		else
			cout << "Ошибка.";

	}

};

// V_KV - V_CIRC = объем оставшегося квадрата.

int main()
{
	setlocale(LC_ALL, "");
	Proverka pr(2, 1);
}

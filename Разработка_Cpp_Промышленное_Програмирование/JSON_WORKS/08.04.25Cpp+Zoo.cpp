#include <iostream>
using namespace std;

class BaseMob {
	string name, say, type="SomeBody";

public:
	BaseMob(string nm, string sy, string tp) : name(nm), say(sy), type(tp) {}

	virtual void info() {
		cout << "Имя: " << name << endl;
		cout << "Звук: " << say << endl;
		cout << "Тип создания: " << type << endl;
	}
};

class Edic : public BaseMob {
	string shutochki;
public:
	Edic(string nm, string sy, string tp, string shtch) : BaseMob(nm, sy, tp), shutochki(shtch) {}

	void info() override {
		BaseMob::info();
		cout << "Шуточки Эдика: " << shutochki << " из 10" << endl << endl;
	}
};

class Cat : public BaseMob {
	string color;
public:
	Cat(string nm, string sy, string tp, string clr) : BaseMob(nm, sy, tp), color(clr) { tp = "Cat"; sy = "Meow"; }

	void info() override {
		BaseMob::info();
		cout << "Кошка раскраски: " << color << endl;
	}
};

class Parrot : public BaseMob {
	string color;

public:
	Parrot(string nm, string sy, string tp, string clr) : BaseMob(nm, sy, tp), color(clr) { tp = "Parrot"; sy = "Craw"; }
	void info() override {
		BaseMob::info();
		cout << "Попугай раскраски: " << color << endl;
	}
};


int main()
{
	setlocale(LC_ALL, "");
	cout << "Добро пожаловать в Зоопарк !!!" << endl;
	Edic ed("Edic", "Ыыыы-ааа", "Mb Human", "10000 львов");
	ed.info();

	Cat c("Муська", "ЖОПААА", "Cats", "Оранжевая, уличная такая.\n");
	c.info();

	Parrot prt("Попка", "АААА!!!!", "Птички", "Желтый с розовыми щечками");
	prt.info();
}

#include <iostream>
#include <string>
using namespace std;


class Passport {
	string numbers, data, fullname;

public:
	Passport(string num, string dt, string fn) : fullname(fn), numbers(num), data(dt){}

	virtual void display() {
		cout << "Номер паспорта: " << numbers << endl;
		cout << "ФИО: " << fullname<< endl;
		cout << "Возраст: " << data << endl;
	}
	void update_Info(string nm, string fn, string d) {
		cout << "\nБыли введены новые паспортные данные\n" << endl;
		cout << "Номер паспорта: " << nm << endl;
		cout << "ФИО: " << fn << endl;
		cout << "Возраст: " << d << endl;
		numbers = nm; fullname = fn; data = d;
	}
};

class ForeignPassport : public Passport {
	string VizaCode;
public:
	ForeignPassport(string num, string dt, string fn, string vc): Passport(num, dt, fn), VizaCode(vc){}
	void display() override {
		Passport::display();
		cout << "Номер карточки Визы: " << VizaCode << endl;
	}
	void update_Info(string nm, string fn, string d, string vc) {
		Passport::update_Info(nm, fn, d); VizaCode = vc;
		cout << "Новый номер карточки Визы: " << VizaCode << endl;
	}
};


int main()
{
	setlocale(LC_ALL, "");
	cout << "---------- " << endl;
	ForeignPassport FP("123-321-1321132", "18", "Kasey!", "Brawl_Stars_VIZA");
	FP.display();
	FP.update_Info("9545905530", "Леон", "10", "Увынск_VIZA");

}

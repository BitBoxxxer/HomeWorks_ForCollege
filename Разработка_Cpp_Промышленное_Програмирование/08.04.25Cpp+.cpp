#include <iostream>
using namespace std;


class Human {
protected:
	string name, sname;
	int age;

public:
	Human(string nm, string snm, int a) : name(nm), sname(snm), age(a) {}

	virtual void info() {
		cout << "Имя: " << name << endl;
		cout << "Фамилия: " << sname << endl;
		cout << "Возраст: " << age << endl;
	}
};

class Student : public Human {
	string group;
public:
	Student(string nm, string snm, int a, string gr) : Human(nm,snm,a), group(gr) {}

	void info() override {
		Human::info();
		cout << "Группа: " << group << endl;
	}
};

int main()
{
	setlocale(LC_ALL, "");
	Student st("Tom", "Tayon", 20, "11-1 RPO");
	st.info();
}

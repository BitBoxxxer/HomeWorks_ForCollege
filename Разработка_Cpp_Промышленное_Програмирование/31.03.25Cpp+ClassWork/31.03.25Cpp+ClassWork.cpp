#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Point {
	int x, y;

	bool operator == (const Point& other) const {
		return x == other.x && y == other.y;
	}

	bool operator != (const Point& other) const {
		return!(*this == other);
	}
};

struct Drob {
	double chis, znam;

	double devision(int dirst, int secod) {
		return dirst / secod;
	}

	bool operator == (const Drob& other) const {
		return other.znam * this->chis == other.chis * this->znam;
	}
	bool operator <= (const Drob& other) const {
		return other.znam * this->chis <= other.chis * this->znam;
	}
	bool operator >= (const Drob& other) const {
		return other.znam * this->chis >= other.chis * this->znam;
	}
	bool operator > (const Drob& other) const {
		return other.znam * this->chis > other.chis * this->znam;
	}
	bool operator < (const Drob& other) const {
		return other.znam * this->chis < other.chis * this->znam;
	}
	bool operator != (const Drob& other) const {
		return other.znam * this->chis != other.chis * this->znam;
	}

	void pow(double n) {
		chis = exp(n * (log(chis)));
		znam = exp(n * (log(znam)));
	}

	void operator ^(double n) {
		chis = exp(n * (log(chis)));
		znam = exp(n * (log(znam)));
	}

	friend ostream& operator << (ostream& os, const Drob& dr);
};

ostream& operator << (ostream& os, const Drob& dr) {
	os << dr.chis << '/' << dr.znam << endl;
	return os;
}

istream& operator>>(istream& is, Drob& dr) {
	cout << "Input chis: ";
	string chis, znam;
	getline(is, chis);
	cout << "Input znam: ";
	getline(is, znam);
	dr.chis = stod(chis);
	dr.znam = stod(znam);
	return is;

}

int main()
{
	Drob a{2,3};
	Drob a1{ 4,9 };
	/*cout << (a == a1) << endl;
	cout << (a <= a1) << endl;
	cout << (a >= a1) << endl;*/

	a.pow(3);
	cout << a.chis << '/' << a.znam << endl;
	a.pow(0.5);
	cout << a.chis << '/' << a.znam << endl;

	Drob b{ 4, 5 };
	b^2;
	cin >> b;
	b ^ 2;
	cout << b;
}

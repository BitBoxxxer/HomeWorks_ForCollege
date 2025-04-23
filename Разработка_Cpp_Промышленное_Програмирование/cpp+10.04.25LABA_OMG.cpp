#include <iostream>
#include <sstream>

using namespace std;

struct Complex {
    int real, img;

    Complex() : real(0), img(1) {}
    Complex(int r, int i) : real(r), img(i) {}

    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, img + other.img);
    }

    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, img - other.img);
    }

    Complex operator*(const Complex& other) const {
        return Complex(real * other.real - img * other.img,
            real * other.img + img * other.real);
    }

    Complex operator/(const Complex& other) const {
        if (other.real == 0 && other.img == 0) {
            cout << "Деление на 0. Ты совсем дурак ?" << endl;
            return Complex(0, 0);
        }
        int denominator = other.real * other.real + other.img * other.img;
        return Complex((real * other.real + img * other.img) / denominator,
            (img * other.real - real * other.img) / denominator);
    }

    bool operator==(const Complex& other) const {
        return (real == other.real && img == other.img);
    }

    bool operator!=(const Complex& other) const {
        return !(*this == other);
    }

    bool operator<(const Complex& other) const {
        return (real < other.real) || (real == other.real && img < other.img);
    }

    bool operator>(const Complex& other) const {
        return (real > other.real) || (real == other.real && img > other.img);
    }

    friend ostream& operator<<(ostream& os, const Complex& c) {
        os << c.real;
        if (c.img >= 0)
            os << "+";
        os << c.img << "i";
        return os;
    }

    friend istream& operator>>(istream& is, Complex& c) {
        char sign;
        char i;
        is >> c.real >> sign >> c.img >> i;
        if (i != 'i' || (sign != '+' && sign != '-'))
            is.setstate(ios::failbit);
        if (sign == '-')
            c.img = -c.img;
        return is;
    }
};

int main() {
    setlocale(LC_ALL, "");
    Complex a(3, 4), b(1, 2);
    Complex sum = a + b;
    Complex diff = a - b;
    Complex prod = a * b;
    Complex quot = a / b;

    cout << "Сумма: " << sum << endl;
    cout << "Разность: " << diff << endl;
    cout << "Произведение: " << prod << endl;
    cout << "Частное: " << quot << endl;
    cout << "a == b: " << (a == b) << endl;
    cout << "a != b: " << (a != b) << endl;
    cout << "a < b: " << (a < b) << endl;
    cout << "a > b: " << (a > b) << endl;

    Complex c;
    cout << "Введите комплексное число в формате a+bi: ";
    cin >> c;

    if (cin)
        cout << "Вы ввели: " << c << endl;
    else 
        cout << "Ошибка ввода, пожалуйста, введите в формате a+bi." << endl;
}
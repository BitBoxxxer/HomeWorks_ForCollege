#include <iostream>
using namespace std;

struct Point {
private:
    int x, y;
public:
    Point() { x = 0; y = 0; }
    Point(int a, int b)
    {
        x = a; y = b;
    }
    int getX()
    {
        return x;
    }
    int getY()
    {
        return y;
    }
};

struct Treygol
{
private:
    Point A, B, C;
    double AB(Point a, Point b)
    {
        return sqrt(pow(a.getX() - b.getX(), 2) + pow(a.getY() - b.getY(), 2));
    }
    double BC(Point a, Point b)
    {
        return sqrt(pow(a.getX() - b.getX(), 2) + pow(a.getY() - b.getY(), 2));
    }
    double AC(Point a, Point b)
    {
        return sqrt(pow(a.getX() - b.getX(), 2) + pow(a.getY() - b.getY(), 2));
    }
public:
    Treygol(Point a, Point b, Point c)
    {
        if ((AB(a,b) < BC(b,c) + AC(a,c)) && (BC(a,b) < AC(b,c) + AB(a,c)) && (AC(a,b) < AB(b,c) + BC(a,c)))
        {
            cout << "OK!";
            A = a; B = b; C = c;
        }
        else 
            cout << "Not a Triangle!";
    }
    double Perimetr()
    {
        return AB(A, B) + BC(B, C) + AC(A, C);
    }
    double Square()
    {
        return sqrt(Perimetr()/2*(Perimetr()/2 - AB(A,B)) * (Perimetr()/2 - BC(B,C)) * (Perimetr()/2 - AC(A,C)));
    }

};

// 2-ая ЧАСТЬ.

struct Square // хватит трех координат одной точки для прорисовки куба, у него же равные стоороны.
{
private:
    Point A, B;
public:
    Square(Point a, Point b, Point c, Point d) {
        cout << "Input A.x: ";
        int a_x = 0; cin >> a_x;
        cout << "Input A.y: ";
        int a_y = 0; cin >> a_y; Point A(a_x, a_y);

        cout << "Input B.x: ";
        int b_x = 0; cin >> b_x;
        cout << "Input B.y: ";
        int b_y = 0; cin >> b_y; Point B(b_x, b_y);
    }
};

struct Kub // КУУУУБ!!!
{
private:
    Square A;
public:
    Kub()
    {
        a;
    }
    double volume()
    {
        return;
    }
};


int main()
{
    cout << "Input A.x: ";
    int a_x = 0; cin >> a_x;
    cout << "Input A.y: ";
    int a_y = 0; cin >> a_y;

    cout << "Input B.x: ";
    int b_x = 0; cin >> b_x;
    cout << "Input B.y: ";
    int b_y = 0; cin >> b_y;

    cout << "Input C.x: ";
    int c_x = 0; cin >> c_x;
    cout << "Input C.y: ";
    int c_y = 0; cin >> c_y;


    Point A(a_x, a_y), B(b_x, b_y), C(c_x, c_y);
    Treygol Trey(A, B, C);
    cout << endl << Trey.Perimetr() << endl;
    cout << Trey.Square() << endl;
}

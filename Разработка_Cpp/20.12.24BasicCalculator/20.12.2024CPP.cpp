
#include <iostream>
using namespace std;

int main()
{
    // 1 задание

    /*int bal1, bal2, bal3, bal4, bal5;
    
    cin >> bal1; cin >> bal2; cin >> bal3; cin >> bal4; cin >> bal5;

    if (((bal1 + bal2 + bal3 + bal4 + bal5) / 5) >= 4)
        cout << "\nAccept to the exam. Good job\n";
    else
        cout << "\nYour were kicked out from College!! Bad job.\n";*/


    // 2 задание

    /*int number;
    cin >> number;

    if (number % 2 == 0)
    {
        cout << ("\n even number: number*3 = "); cout << (number * 3);
    }
    else
    {
        cout << ("\n number not even: number/2 = "); cout << number / 2;
    }*/


    // 3 задание

    int numberA, numberB; char Operation;

    cout << "\nenter A: "; cin >> numberA;
    cout << "enter B: "; cin >> numberB;

    cout << "\nenter the operation for this numbers: [+ - / *]: "; cin >> Operation;

    switch (Operation)
    {
        case '+':
            cout << "\noperation '+': [A + B] = "; cout << numberA + numberB; cout << "\n";
            break;
        case '-':
            cout << "\noperation '-': [A - B] = "; cout << numberA - numberB; cout << "\n";
            break;
        case '*':
            cout << "\noperation '*': [A * B] = "; cout << numberA * numberB; cout << "\n";
            break;
        case '/':
            if (numberB == 0)
                cout << "\nerror, B can't be '0'\n";
            else
            {
                cout << "\noperation '/': [A / B] = "; cout << numberA / numberB; cout << "\n";
            }
            break;
        default: cout << "Ошибка";
    }
}

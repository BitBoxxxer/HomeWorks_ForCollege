#include <iostream>
using namespace std;

/* Вопросы по CPP
1 - Как писать в выводе строку и переменную ( как в C# через {}) ?
2 - Как очищать консоль после выполнения команды 
(В C# это делается через команду 'Clear();') ?
*/

int main()
{
    //const int n = 50; // константа не будет менять свое значение.
    //int arr[n]{};

    //int l = 0;
    //for (int i = 2; i < 10000; i++)
    //{
    //    int k = 0;
    //    for (int j = 2;j < i / 2 + 1;j++)
    //    {
    //        if (i % j == 0)
    //        {
    //            k = 1; break;
    //        }
    //    }
    //    if (k == 0)
    //    {
    //        if (l == 50)
    //            break;
    //        arr[l] = i;
    //        l++;
    //    }
    //}
    /*for (int i = 0; i < n; i++)
    {
        cout << arr[i] << endl;
    }*/


    // Задание 1

    /*int count = 0; int input;

    for (int n = 1; n < 7; n ++)
    {
        cout << "The profit: (" << n << " Month)\n";
        cin >> input;

        count += input;

        if(n == 6)
            cout <<"Result: " << count;
    }*/

    // Задание 2

    /*int arrMonth[6]{1,2,3,4,5,6};

    for (int i = 5; i >= 0; i--)
    {
        cout << arrMonth[i] << endl;
    }*/


    // Задание 3

    /*int numbers[5]; int count = 0;
    int xs;

    for (int i = 0; i < 5; i++)
    {
        cout << "Enter '" << i+1 << "' storony: ";
        cin >> xs;
        numbers[xs];
        count += xs;

        if (i == 4)
        {
            cout << "Result: " << count;
        }
    }*/

    // Задание 4

    int min = INT_MAX;
    int max = INT_MIN;
    int val;
    for (int i = 0; i < 12; i++) {
        cout << "Enter the money for '" << i << "'Month: ";
        cin >> val;
        if (val > max) {
            max = val;
        }
        if (val < min) {
            min = val;
        }
    }
    cout << "\nResult: \nMax money = " << max << endl;
    cout << "Min money = " << min << endl;

}

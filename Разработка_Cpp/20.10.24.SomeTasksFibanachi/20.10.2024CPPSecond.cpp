#include <iostream>
using namespace std;

int main()
{
    int n = 0, sum = 0;
    cin >> n;

    int fiba; int f1 = 1; int f2 = 0;

    for (int i = 1; i <= n; i++)
    {
        fiba = f1 + f2;
        f2 = f1;
        f1 = fiba;

        if (i < n)
        {
            cout << fiba + ", ";
        }
        else
            cout << fiba;
    }


    /*int i = 1;
    while (i <= n) // 2-ая задача
    {
        if (i % 2 == 0)
            sum += -i;
        else
            sum += i;
        i++;

    }
    cout << sum;*/

    /*for (int i = 1; i <= n; i++)
    {
        if (i % 2 == 0)
            sum += (-i);
        else
            sum += i;
    }
    cout << sum;*/

}

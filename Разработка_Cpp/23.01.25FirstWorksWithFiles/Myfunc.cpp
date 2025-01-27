#include "Myfunc.h"
#include <time.h>
#include <iostream>

int sum(int a, int b)
{
    return a + b;
}

int max_index(int a[], int n)
{
    int max_count = 0;
    int max = 0;
    for (int i = 0; i <= n; i++)
        if (a[i] > max)
        {
            max = a[i];
            max_count = i;
        }
    return max_count + 1;
}

void zapolnenie(int* a, int n)
{
    srand(time(0));
    for (int i = 0; i < n; i++)
    {
        a[i] = rand() % 1000;
    }
}

void print(int* a, int n)
{
    for (int i = 0; i < n; i++)
    {
        std::cout << a[i] << " ";
        if ((i % 10 == 0) and (i != 0))
            std::cout << "\n";
    }
}

void prst_search(int* a, int n)
{
    int cnt = 0;

    for (int i = 0; i < n; i++)
    {
        int k = 0;
        for (int j = 2; j * j < a[i];j++)
        {
            if (a[i] % j == 0)
                k++;
        }
        if (k == 0)
            cnt ++;
    }
    std::cout << "Otvet: " << cnt;
}

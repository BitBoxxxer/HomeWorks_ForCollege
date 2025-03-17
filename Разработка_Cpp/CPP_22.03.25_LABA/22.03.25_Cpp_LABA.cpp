#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<int> result;
    for (int i = 45000000; i <= 50000000; i++) {
        int count = 0;
        vector<int> numbers_vectr;
        for (int j = 1; j * j <= i; j += 2)
        {
            if (i % j == 0)
            {
                if (i / j == j)
                {
                    numbers_vectr.push_back(j);
                    count++;
                }
                else
                {
                    numbers_vectr.push_back(j);
                    numbers_vectr.push_back(i / j);
                    count += 2;
                }
            }
        }
        if (numbers_vectr.size() == 5)
            result.push_back(i);
    }
    for (int num : result)
        cout << num << endl;
}
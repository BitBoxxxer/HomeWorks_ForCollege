#include <iostream>
#include "Myfunc.h"
using namespace std;

int main()
{
	int n = 100;
	int* a = new int [n] {};
	zapolnenie(a, n);
	print(a,n);
	prst_search(a, n);

}

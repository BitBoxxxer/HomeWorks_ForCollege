#include <iostream>
#include <vector>
using namespace std;
// работает по типу таблицы умножения.

string alphavet;

vector<vector<char>> table_vizjiner()
{
	const int n = 26;
	vector <vector<char>> table(n, vector<char>(n));
	for (int i = 97; i < 123; i++)
		alphavet += char(i);

	for (int i = 0; i < 26; i++)
		for (int j = 0; j < 26; j++)
			table[i][j] = alphavet[(i + j) % 26];

	cout << "\nМатрица:\n";
	for (int i = 0; i < 26; i++)
	{
		for (int j = 0; j < 26; j++)
			cout << table[i][j] << " ";
		cout << endl;
	}
	return table;
}

string new_key(string key, string slovo)
{
	string nkey = key;
	int count = 0;
	while (nkey.size() != slovo.size())
	{
		nkey += key[count % key.size()];
		count++;
		if (nkey.size() == slovo.size())
			break;
	}
	return nkey;
}

int search_place(char c)
{
	for (int i = 0; i < size(alphavet); i++)
		if (c == alphavet[i])
			return i;
}

string shifr_vizhenera(string old_key, string slovo)
{
	vector<vector<char>> table(26, vector<char>(26));
	table = table_vizjiner();
	string key = new_key(old_key, slovo);
	string crepy;
	for (int i =0; i < size(slovo); i++)
	{
		int row=0, coll=0;

		coll = search_place(slovo[i]);
		row = search_place(key[i]);
		crepy += table[row][coll];
	}
	return crepy;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	string key, slovo;
	cout << "\nВведите ключ: ";cin >> key;
	cout << "\nВведите слово: ";cin >> slovo;

	cout <<"\nНовый ключ: "<< new_key(key, slovo) << endl;
	cout << "Шифр Виженера: "<<shifr_vizhenera(key, slovo) << endl;
}

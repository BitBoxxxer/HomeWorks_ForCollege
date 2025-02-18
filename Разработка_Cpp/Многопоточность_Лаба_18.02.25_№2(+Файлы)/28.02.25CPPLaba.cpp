#include <iostream>
#include <thread>
#include <vector>
#include <filesystem>
#include <mutex>
#include <fstream>
#include <cctype>

using namespace std;
using namespace filesystem;

int tcount = 0;
mutex mtx;

void f(const path& pth) // при ссылках для потоков нужно использовать const.
{
	ifstream f(pth);
	int words = 0; string word;
	while (f >> word)
	{
		words++;
	}
	lock_guard<mutex>lock(mtx);
	tcount += words;
	cout << "Filename " << pth.filename() << ".Wordcount: " << words << endl
		 << "Path: " << pth << endl << '\n';
}

int main()
{
	string _filename;
	cout << "Ur filename: ";
	cin >> _filename;

	int FileSimvolsCount = 0;

	//"C:\\Users\\A\\source\\repos\\28.02.25CPPLaba\\28.02.25CPPLaba\\ne_aboba.txt.txt"

	ifstream os;
	string filespath = "C:\\Users\\A\\source\\repos\\28.02.25CPPLaba\\28.02.25CPPLaba\\";
	
	os.open(filespath + _filename + ".txt");
	if (os.is_open())
	{
		cout << "file is real" << endl;

		char simword;
		while (os >> simword)
		{
			if (isalpha(simword))
				FileSimvolsCount++;
		}
		cout << "FileSimvols = " << FileSimvolsCount << endl;
	}

	path pth = current_path(); 

	vector <path> files;

	if (exists(pth) and is_directory(pth))
	{
		for (const auto& entry : directory_iterator(pth))
			if (entry.path().extension() == ".txt")
				files.push_back(entry.path());

		int thr_count = 0;

		if (files.size() < thread::hardware_concurrency())
			thr_count = files.size();
		else
			thr_count = thread::hardware_concurrency();

		vector<thread> thrd;

		for (int i = 0; i < thr_count; i++)
			thrd.emplace_back(f, files[i]);
		for (auto& i : thrd)
			i.join();
	}
	cout << "\nAll word count from txt files: " << tcount;
	// добавить чтение по символам, через char кодировкой юникодом считать символы букв.
}

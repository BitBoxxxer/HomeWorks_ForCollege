#include <iostream>
using namespace std;

class Student {
protected:
	string country, city, telephon, fullname, birthdate, college;
public:

	Student() : country("DEBUGcountry"), city("DEBUGcity"), telephon("DEBUGtelephone"), fullname("DEBUGfullname"), birthdate("DEBUGbirthdate"), college("DEBUGcolege") {}

	void input() {
		cout << "Input country: ";
		cin >> country;
		cout << "Input city: ";
		cin >> city;
		cout << "Input telephon: ";
		cin >> telephon;

		cout << "Input fullname: ";
		cin >> fullname;
		cout << "Input birthdate: ";
		cin >> birthdate;
		cout << "Input college: ";
		cin >> college;

	}
	void print() {
		cout << "\nFull Info: " << endl;
		cout << "\ncountry: " << country <<"\ncity: " << city << "\ntelephone: " << telephon <<
			"\nfullname: " << fullname <<"\nbirthdate: " << birthdate <<"\ncollege: "
			<< college;
	}
};

class CardStudent : protected Student {
public:
    CardStudent(const Student& stud) : Student(stud) {}

    void search() {
        string choice;
        cout << "What do you want to find: " << endl;
        cout << "1 - Fullname; 2 - Birthdate; 3 - College; 4 - Country; 5 - City; 6 - Telephone; ";
        cin >> choice;

        if (choice == "1")
            cout << "Fullname: " << fullname << endl;
        else if (choice == "2")
            cout << "Birthdate: " << birthdate << endl;
        else if (choice == "3")
            cout << "College: " << college << endl;
        else if (choice == "4")
            cout << "Country: " << country << endl;
        else if (choice == "5")
            cout << "City: " << city << endl;
        else if (choice == "6")
            cout << "Telephone: " << telephon << endl;
        else
            cout << "Error" << endl;
    }
};


int main()
{
	Student a;
	a.input();
	a.print();

    CardStudent b(a);
    b.search();

}

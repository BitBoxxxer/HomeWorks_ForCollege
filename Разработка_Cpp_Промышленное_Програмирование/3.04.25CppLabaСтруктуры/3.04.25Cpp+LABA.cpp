#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

vector<string> BooksList;

struct Book
{
private:

    string Author, Title, Publisher;
    int Year, Number_pages;

    void author(/*string name*/)
    {
        cout << "author name: ";
        cin >> this->Author;
    }
    void publish()
    {
        cout << "publish house name: ";
        cin >> this->Publisher;
    }
    void pub_title()
    {
        cout << "book name: ";
        cin >> this->Title;
        BooksList.push_back(this->Title);
    }
    void year_pub()
    {
        cout << "year for book: ";
        cin >> this->Year;
    }
    void pub_numberPag()
    {
        cout << "numbers pages for book: ";
        cin >> this->Number_pages;
    }

public:
    Book()
    {
        ofstream File("file_for_books.txt");

        this->author();
        this->pub_title();
        this->publish();
        this->year_pub();
        this->pub_numberPag();

        File << this->Author << ' ' << this->Publisher << ' ' << this->Title << ' ' << this->Year << ' ' << this->Number_pages << endl;
        File.close();
    }
    void author_find_book(string nm_auth)
    {
        ifstream ReadFile("file_for_books.txt");string text; int count = 0;
        while (getline(ReadFile, text))
        {
            if (count == 0)
                if (this->Author == nm_auth)
                    cout << this->Title << endl;
            count++;
        }

        ReadFile.close();
    }
    void house_finds_book(string nm_house)
    {
        ifstream ReadFile("file_for_books.txt"); string text; int count = 0;
        while (getline(ReadFile, text))
        {
            if (count = 1)
                if (this->Publisher == nm_house)
                    cout << this->Title << endl;
            count++;
        }

        ReadFile.close();
    }
    void year_finds_book(int year)
    {
        ifstream ReadFile("file_for_books.txt");string text; int count = 0;
        while (getline(ReadFile, text))
        {
            if (count = 3)
                if (this->Year > year)
                    cout << this->Title << endl;
            count++;
        }

        ReadFile.close();
    }
};

int main()
{
    
    vector <Book> books; int n = 1;
    for (int i = 0; i < n; i++)
    {
        Book a; books.push_back(a);
    }

    cout << "\nInput author name: ";
    string s; cin >> s;
    for (int i = 0; i < n; i++)
    {
        books[i].author_find_book(s);
    }

    cout << "\nInput House name: ";
    string s2; cin >> s2;
    for (int i = 0; i < n; i++)
        books[i].house_finds_book(s2);

    cout << "\nInput Year: ";
    int s3; cin >> s3;
    for (int i = 0; i < n; i++)
        books[i].year_finds_book(s3);

    cout << "Books List: \n";
    for (string j : BooksList)
        cout << j << ' ';
}

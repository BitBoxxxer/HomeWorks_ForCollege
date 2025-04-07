#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Address {
public:
    string city;
    string street;
    int houseNum;
    int apartmentNum;
};
struct Student {
public:
    string fullName;
    int age;
    string recordBookNumber;
    double averageScore;
    Address address;
};
struct Node {
public:
    Student data;
    Node* next;

    Node(const Student& student) { data = student; next = nullptr; }
};
class StudentList {
private:
    Node* head;
    Node* tail;
    int lnght;

public:
    StudentList() { head = nullptr; tail = nullptr; lnght = 0; }

    ~StudentList() { }

    void addStudent(const Student& student) {
        Node* newNode = new Node(student);
        if (head == nullptr) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
        lnght++;
    }

    bool deleteStudent(const string& recordBookNumber) {
        Node* current = head;
        Node* previous = nullptr;

        while (current != nullptr) {
            if (current->data.recordBookNumber == recordBookNumber) {
                if (previous == nullptr) 
                    head = current->next;
                else 
                    previous->next = current->next;
                if (current == tail) 
                    tail = previous;
                delete current;
                lnght--;
                return true;
            }
            previous = current;
            current = current->next;
        }
        return false;
    }

    Student* findStudent(const string& recordBookNumber) {
        Node* current = head;
        while (current != nullptr) {
            if (recordBookNumber == current->data.recordBookNumber) {
                cout << "GOOD.";
                return &current->data;
            }
            current = current->next;
        }
        cout << "";
    }


    void printStudents() {
        Node* current = head;
        while (current != nullptr) {
            cout << current->data.fullName << ", Возраст: " << current->data.age
                << ", Номер зачетки: " << current->data.recordBookNumber << ", Средний балл: "
                << current->data.averageScore << ", Адрес: " << current->data.address.city
                << ", " << current->data.address.street << ", д." << current->data.address.houseNum
                << ", кв." << current->data.address.apartmentNum << endl;
            current = current->next;
        }
    }

    double AverageScore() {
        if (lnght == 0) return 0.0;
        double totalScore = 0.0;
        Node* current = head;
        while (current != nullptr) {
            totalScore += current->data.averageScore;
            current = current->next;
        }
        return totalScore / lnght;
    }

    void clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        lnght = 0;
    }

    void saveToFile(const string& filename) {
        ofstream outFile(filename);
        Node* current = head;
        while (current != nullptr) {
            outFile << current->data.fullName << endl
                << current->data.age << endl
                << current->data.recordBookNumber << endl
                << current->data.averageScore << endl
                << current->data.address.city << endl
                << current->data.address.street << endl
                << current->data.address.houseNum << endl
                << current->data.address.apartmentNum << endl;
            current = current->next;
        }
        outFile.close();
    }

    void loadFromFile(const string& filename) {
        ifstream inFile(filename);
        while (inFile) {
            Student student;
            getline(inFile, student.fullName);
            if (inFile.eof()) break;
            inFile >> student.age;
            inFile.ignore();
            inFile.ignore();
            getline(inFile, student.recordBookNumber);
            inFile >> student.averageScore;
            inFile.ignore();
            getline(inFile, student.address.city);
            getline(inFile, student.address.street);
            inFile >> student.address.houseNum;
            inFile >> student.address.apartmentNum;
            inFile.ignore();

            addStudent(student);
        }
        inFile.close();
    }
};

int main() {

    setlocale(LC_ALL, "Russian");
    StudentList studentList;
    Address address1 = { "Москва", "Ленина", 10, 5 };
    Student student1 = { "Арбуз Вазгенович", 20, "123456", 4.5, address1 };
    studentList.addStudent(student1);
    Address address2 = { "Санкт-Петербург", "Пушкина", 15, 2 };
    Student student2 = { "Дыня", 22, "654321", 3.8, address2 };
    studentList.addStudent(student2);
    cout << "\nСписок студентов:" << endl;
    studentList.printStudents();
    cout << "\nСредний балл всех студентов: " << studentList.AverageScore() << endl;
    studentList.saveToFile("students.txt");
    studentList.clear();

    studentList.loadFromFile("students.txt");
    cout << "\nПосле загрузки из файла:" << endl;
    studentList.printStudents();
    string recordBookNumberToFind = "123456";
    Student* foundStudent = studentList.findStudent(recordBookNumberToFind);
    cout << foundStudent;
    if (foundStudent != NULL)
        cout << "\nНайден Студент с номером зачетки " << recordBookNumberToFind << endl;
    else
        cout << "\nСтудент с номером зачетки " << recordBookNumberToFind << " не найден." << endl;

}

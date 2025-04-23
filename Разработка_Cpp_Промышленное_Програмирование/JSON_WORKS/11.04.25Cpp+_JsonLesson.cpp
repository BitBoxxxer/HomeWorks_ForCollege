#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <memory>

using namespace std;
using json = nlohmann::json;

class PersoneExcept : public runtime_error {
public:
    using runtime_error::runtime_error;
};

class Employee {
protected:
    string name, pos;
public:
    Employee(string nm, string p) : name(nm), pos(p) {
        if (name.empty()) PersoneExcept("ИМЯ ПУСТОЕ БАЛДАААА !!!");
        if (pos.empty()) PersoneExcept("Позиция ПУСТОЕ БАЛДАААА !!!");
    }

    virtual void showinfo() = 0;
    virtual double calculateSalary() = 0;
    virtual string gettype() const = 0;

    virtual json tojson() const {
        return
        {
            {"type", gettype()},
            {"name", name},
            {"position", pos}
        };
    }

    virtual void fromjsom(const json& j) {
        name = j.at("name").get<string>();
        pos = j.at("position").get<string>();
    }

    virtual ~Employee() = default;
};

class Director : public Employee {
    string department;
    int exp;
public:
    Director(string nm, string depart, int e) : Employee(nm, "Director"), department(depart), exp(e) {
        if (department.empty()) PersoneExcept("Департамент не может быть пустым.");
        if (exp < 5) PersoneExcept("НУЖНО БОЛЬШЕ ОПЫТА !!!");
    }

    void showinfo() override {
        cout << "Имя " << name << endl;
        cout << "Директор " << department << endl;
        cout << "Опыт работы " << exp << endl;
    }

    double calculateSalary() override {
        return 100000 + exp * 1000;
    }

    string gettype() const override {
        return "director";
    }

    json tojson() const override {
        json j = Employee::tojson();
        j["department"] = department;
        j["experience"] = exp;
        return j;
    }

    void fromjsom(const json& j) override {
        Employee::fromjsom(j);
        department = j.at("department").get<string>();
        exp = j.at("experience").get<int>();
    }
};

void save_to_json_file(const vector<unique_ptr<Employee>>& employees, const string& filename) {
    json j_array;
    for (const auto& employee : employees) {
        j_array.push_back(employee->tojson());
    }
    ofstream outfile(filename);
    if (!outfile.is_open()) {
        throw runtime_error("Не удалось открыть файл для записи: " + filename);
    }
    outfile << j_array.dump(4) << endl;
    outfile.close();
}

vector<unique_ptr<Employee>> load_from_json_file(const string& filename) {
    vector<unique_ptr<Employee>> employees;
    ifstream infile(filename);
    if (!infile.is_open()) {
        throw runtime_error("Не удалось открыть файл для чт: " +filename);
    }

    json j_array;
    infile >> j_array;
    infile.close();

    for (const auto& j : j_array) {
        string type = j.at("type").get<string>();
        unique_ptr<Employee> employee;

        if (type == "director") {
            employee = make_unique<Director>("", "", 0);
        }
        employee->fromjsom(j);
        employees.push_back(move(employee));

    }
    return employees;
}

int main() {
    setlocale(LC_ALL, "Russian");
    vector<unique_ptr<Employee>> employees;
    string filename = "rabota.json";

     employees.push_back(make_unique<Director>("Ivan", "Gazprom", 10));
     employees.push_back(make_unique<Director>("Petr", "Rosneft", 6));

     save_to_json_file(employees, filename);
     cout << "Сохранено в " << filename << endl;

     employees.clear();

     employees = load_from_json_file(filename);
     cout << "Загружено из " << filename << endl;

     for (auto& employee : employees) {
         employee->showinfo();
         cout << "Зарплата: " << employee->calculateSalary() << endl << endl;
     }
}

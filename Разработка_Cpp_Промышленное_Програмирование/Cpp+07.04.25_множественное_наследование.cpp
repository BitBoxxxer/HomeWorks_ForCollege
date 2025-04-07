#include <iostream>
#include <vector>
using namespace std;


class Koleso
{
protected:
    int koleso_r;
    double koleso_C;
    string koleso_firm_name;

public:
    Koleso() { koleso_r = 1; koleso_firm_name = "No_Firm_Name"; }
    Koleso(int k_r) { double C = 2 * 3.14 * k_r; koleso_C = C; }

    double status() {
        return koleso_C;
    }
};


class Engine
{
protected:
    int moto_moshnost, moto_V;
    bool is_run = false;

public:
    Engine() { moto_moshnost = 0; moto_V = 0; }
    Engine(int m_m, int m_v) { moto_moshnost = m_m; moto_V = m_v; }

    bool start() {
        is_run = true;
        return is_run;
    }

    bool stop() {
        is_run = false;
        return is_run;
    }

    bool status() {
        return is_run;
    }

    int get_v() {
        return moto_V;
    }

    int get_mosh() {
        return moto_moshnost;
    }
};

class Body {
protected:
    string color;
public:
    Body() { color = "Defolt_White"; }
    Body(string col) { color = col; }

    void re_paint(string c) {
        color = c;
        cout << "Машина перекрашена в: " << color << "цвет";
    }

    string get_color() {
        return color;
    }
};

class Dveri
{
protected:
    int dver_tolsh;
    bool is_open;

public:
    Dveri() { is_open = false; dver_tolsh = 0; }

    bool start() {
        is_open = true;
        return is_open;
    }

    bool stop() {
        is_open = false;
        return is_open;
    }

    bool status() {
        return is_open;
    }

    int dver_t() {
        return dver_tolsh;
    }
    
};

class Avto : public Engine, public Body
{
protected:
    vector<Koleso> kolesa;
    vector<Dveri> dveri;

public:
    Avto(int eng_mosh, int eng_v, string col, int cnt_koles, int cnt_dver) :
        Engine(eng_mosh, eng_v), Body(col)
    {
        int k_r, d_t;

        cout << "Koleso radius: "; cin >> k_r;
        cout << "Dveri tolshina: "; cin >> d_t;

        for (int i = 0; i < cnt_koles; i++) {
            kolesa.push_back(Koleso(k_r));
        }
        for (int i = 0; i < cnt_dver; i++) {
            dveri.push_back(Dveri());
        }
    }

    void info_kolesa() {
        for (auto i : kolesa) {
            i.status();
        }
    }

    void info_dveri() {
        int indx = 1;
        for (auto i : dveri) {
            if (i.status() == true) {
                cout << "Door is open!" << endl;
            }
            else {
                cout << "Door is close!" << endl;
            }
            indx++;
        }
    }

    void auto_info() {
        cout << "Auto with motor объемом: " << get_v() << endl;
        cout << "Auto with мощностью: " << get_mosh() << endl;

        cout << "Цвет машины: " << get_color() << endl;
        cout << "Кол-во дверей: " << size(dveri) << endl;
        //cout << "Толщина дверей: " << dver_t() << endl;

        cout << "Кол-во колес: " << size(kolesa) << endl;
        cout << "Диаметр колес: " << status() << endl;
    }

};


int main()
{
    setlocale(LC_ALL, "");
    Avto car(10, 5, "black", 4, 4);
    car.auto_info();
}

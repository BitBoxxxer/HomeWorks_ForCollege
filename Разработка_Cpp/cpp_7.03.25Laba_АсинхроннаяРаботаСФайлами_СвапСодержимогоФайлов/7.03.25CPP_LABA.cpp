#include <iostream>
#include <fstream>
#include <future>
#include <string>

using namespace std;

void wr_file(const string& fname, const string& data, void (*callback)(bool)) 
{
    auto task = async(launch::async, [fname, data]() 
        {
        ofstream fl(fname);
        if (!fl.is_open())
            return false;
        fl << data;
        fl.close();
        return true;
        });

    callback(task.get());
}

void rd_file(const string& fname, void (*callback)(bool, const string&)) 
{
    auto task = async(launch::async, [fname]()
        {
        ifstream fl(fname);
        if (!fl.is_open())
            return make_pair(false, string());
        string content, line;
        while (getline(fl, line))
            content += line + "\n";
        fl.close();
        return make_pair(true, content);
        });

    auto result = task.get();
    callback(result.first, result.second);
}

void swp_file(const string& ffname, const string& sfname, void (*callback)(bool)) 
{
    auto task = async(launch::async, [ffname, sfname]() 
        {
        ifstream fl(ffname);
        ofstream f2(sfname);
        if (!fl.is_open() || !f2.is_open())
            return false;
        string s;
        while (getline(fl, s))
            f2 << s << "\n";
        fl.close();
        f2.close();
        return true;
        });

    callback(task.get());
}

void change_swp_file(const string& ffname, const string& sfname, const string& tfname, void (*callback)(bool)) 
{
    auto task = async(launch::async, [ffname, sfname, tfname]() 
        {
        ifstream fl(ffname);
        ifstream f2(sfname);
        ofstream chernovik(tfname);
        if (!fl.is_open() || !f2.is_open() || !chernovik.is_open())
            return false;

        string line;
        while (getline(fl, line))
            chernovik << line << "\n";
        while (getline(f2, line))
            chernovik << line << "\n";

        fl.close();
        f2.close();
        chernovik.close();
        return true;
        });

    callback(task.get());
}

void read_callback(bool flg, const string& content) 
{
    if (!flg)
        cout << "Problem with file (read fl check)" << endl;
    else
        cout << "All is OK :) (read fl check)\nContent:\n" << content << endl;
}

void write_callback(bool flg) 
{
    if (!flg)
        cout << "Problem with file (write fl check)" << endl;
    else
        cout << "All is OK :) (write fl check)" << endl;
}

void swap_callback(bool flg) 
{
    if (!flg)
        cout << "Problem with file (swp fl check)" << endl;
    else
        cout << "All is OK :) (swp fl check)" << endl;
}

void change_swap_callback(bool flg)
{
    if (!flg)
        cout << "Problem with file (change_swp fl check)" << endl;
    else
        cout << "All is OK :) (change_swp fl check)" << endl;
}

int main()
{
    string first_file = "num1.txt";
    string second_file = "buba2.txt";
    string third_file = "chernovik.txt";

    wr_file(first_file, "Hello, Jopa.", write_callback);
    rd_file(first_file, read_callback);
    swp_file(first_file, second_file, swap_callback);
    change_swp_file(first_file, second_file, third_file, change_swap_callback);
}

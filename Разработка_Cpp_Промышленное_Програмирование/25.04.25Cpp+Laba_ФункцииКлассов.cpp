#include <iostream>
using namespace std;

template<typename T>
class Array {
protected:
    T* data;
    int size, count;
    int grow = 1;

    void resize(int new_size) {
        if (size == new_size)
            return;
        T* new_data = new T[new_size];
        int mn = min(size, new_size);
        for (int i = 0; i < mn; i++)
            new_data[i] = data[i];
        delete[] data;
        size = new_size;
        data = new_data;
        if (count > size)
            count = size;
    }
public:
    Array() : data(nullptr), size(0), count(0) {}
    explicit Array(int new_size) : data(nullptr), count(0) { resize(new_size); }
    ~Array() { delete[] data; }

    T& operator[](int index) {
        return data[index];
    }

    Array& operator=(const Array& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            count = other.count;
            data = new T[size];
            for (int i = 0; i < count; i++)
                data[i] = other.data[i];
        }
        return *this;
    }

    int GetSize() const {
        return size;
    }

    void SetSize(int new_size, int new_grow) {
        grow = new_grow;
        if (size == new_size)
            return;
        resize(new_size + grow);
    }

    int GetUpperBound() const {
        return count - 1;
    }

    bool IsEmpty() const {
        return count == 0;
    }

    void FreeExtra() {
        resize(count);
    }

    void RemoveAll() {
        count = 0;
    }

    T GetAt(int index) const {
        if (index < 0 || index >= count) {
            cout << "GA Index out of bounds" << endl; return;
        }
        return data[index];
    }

    void SetAt(int index, const T& v) {
        if (index < 0 || index >= count) {
            cout << "SA Index out of bounds" << endl;
            return;
        }
        data[index] = v;
    }

    void Add(const T& v) {
        if (count >= size)
            resize(size + grow);
        data[count++] = v;
    }

    void Append(const Array<T>& o) {
        for (int i = 0; i < o.count; i++)
            Add(o.data[i]);
    }

    void InsertAt(int index, const T& v) {
        if (index < 0 || index > count) {
            cout << "IA Index out of bounds" << endl;
            return;
        }
        if (count >= size)
            resize(size + grow);

        for (int i = count; i > index; i--)
            data[i] = data[i - 1];
        data[index] = v;
        count++;
    }

    void RemoveAt(int index) {
        if (index < 0 || index >= count) {
            cout << "RA Index out of bounds" << endl;
            return;
        }
        for (int i = index; i < count - 1; i++)
            data[i] = data[i + 1];
        count--;
    }

    T* GetData() {
        return data;
    }
};

int main() {
    setlocale(LC_ALL, "");
    Array<int> ar(5);
    ar.Add(10);
    ar.Add(20);
    ar.Add(50);
    cout << "\n\nРазмер: " << ar.GetSize() << endl;

    for (int i = 0; i < 3; i++)
        cout << ar[i] << " ";
    cout << endl;
}
#include <iostream>

using namespace std;

template <typename T>
class Array {
protected:
    T* data;
    int size;
public:
    Array(int size = 0) : size(size), data(new T[size]{}) {}

    Array(const Array& other) : size(other.size), data(new T[other.size]) {
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }

    Array& operator=(const Array& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new T[size];
            for (int i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    virtual ~Array() {
        delete[] data;
    }

    virtual T& operator[](int index) {
        return data[index];
    }

    int find(const T& value) const {
        for (int i = 0; i < size; i++) {
            if (data[i] == value) return i;
        }
        return -1;
    }

    virtual int getSize() const { return size; }
};

template <typename T>
class SortedArray : public Array<T> {
public:
    SortedArray(int size = 0) : Array<T>(size) {}

    void insert(const T& value) {
        T* newData = new T[this->size + 1];
        int i = 0;

        while (i < this->size && this->data[i] < value) newData[i++] = this->data[i];
        newData[i++] = value;
        while (i <= this->size) newData[i++] = this->data[i - 1];

        delete[] this->data;
        this->data = newData;
        this->size++;
    }

    void remove(const T& value) {
        int index = this->find(value);

        T* newData = new T[this->size - 1];
        for (int i = 0, j = 0; i < this->size; i++) {
            if (i != index) newData[j++] = this->data[i];
        }

        delete[] this->data;
        this->data = newData;
        this->size--;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    SortedArray<int> arr;
    arr.insert(5);
    arr.insert(3);
    arr.insert(8);
    arr.insert(1);

    cout << "Элементы массива: ";
    for (int i = 0; i < arr.getSize(); i++) {
        cout << arr[i] << " ";
    }

    arr.remove(3);
    cout << endl << "После удаления 3: ";
    for (int i = 0; i < arr.getSize(); i++) {
        cout << arr[i] << " ";
    }
}
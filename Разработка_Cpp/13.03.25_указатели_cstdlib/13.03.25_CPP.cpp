#include <iostream>
#include <cstdlib>
using namespace std;

int** vvod(int n, int m) 
{
    int** a = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        a[i] = (int*)malloc(m * sizeof(int));
        for (int j = 0; j < m; j++)
            a[i][j] = rand() % 10;
    }
    return a;
}

void prnt(int** mx, int n, int m) 
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            cout << mx[i][j] << ' ';
        cout << endl;
    }
}

int** mltpl_matrix(int** m1, int n1, int** m2, int n2, int m2_cols)
{
    int** m3 = (int**)malloc(n1 * sizeof(int*));
    for (int i = 0; i < n1; i++) {
        m3[i] = (int*)malloc(m2_cols * sizeof(int));
        for (int j = 0; j < m2_cols; j++) {
            m3[i][j] = 0;
            for (int k = 0; k < n2; k++)
                m3[i][j] += m1[i][k] * m2[k][j];
        }
    }
    return m3;
}

void free_matrix(int** m, int n)
{
    for (int i = 0; i < n; i++)
        free(m[i]);
    free(m);
}

int main() 
{
    setlocale(LC_ALL, "Russian");
    int n = 5, n2 = 5, m2 = 10;
    int** matrix1 = vvod(n, n);
    cout << "Первая матрица:\n";
    prnt(matrix1, n, n);
    int** matrix2 = vvod(n2, m2);
    cout << "Вторая матрица:\n";
    prnt(matrix2, n2, m2);
    int** result_matrix = mltpl_matrix(matrix1, n, matrix2, n2, m2);
    cout << "Третья:\n";
    prnt(result_matrix, n, m2);
    free_matrix(result_matrix, n);
    free_matrix(matrix1, n);
    free_matrix(matrix2, n2);
}

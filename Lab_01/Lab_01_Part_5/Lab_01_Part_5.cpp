#include <omp.h>
#include <iostream>
#include <math.h>
#include <time.h>

using namespace std;

int main() {
    omp_set_num_threads(2);

    setlocale(LC_ALL, "rus");
    system("chcp 1251");
    system("cls");

    clock_t t;

    t = clock();

    int raw, column;

    cout << "Введите количество уравнений:" << endl << "> ";

    cin >> raw;

    cout << "Введите количество переменных:" << endl << "> ";

    cin >> column;

    float** myArray = new float* [raw];

    for (int i = 0; i < raw; i++) myArray[i] = new float[column];

    for (int i = 0; i < raw; i++) {
        for (int j = 0; j < column; j++) {
            cout << "Ввод элемента " << "[" << i + 1 << " , " << j + 1 << "] > ";

            cin >> myArray[i][j];
        }
    }

    cout << "Заданная матрица:" << endl;

    for (int i = 0; i < raw; i++) {
        for (int j = 0; j < column; j++) cout << myArray[i][j] << " ";

        cout << endl;
    }

    cout << endl;

    // Прямой ход метода Гаусса
    for (int i = 0; i < raw; i++) {
        int j, k;
        float temp = myArray[i][i];

        for (j = raw; j >= i; j--) myArray[i][j] /= temp;

#pragma omp parallel for private (j, k, temp)
        for (j = i + 1; j < raw; j++) {
            temp = myArray[j][i];

            for (k = raw; k >= i; k--) myArray[j][k] -= temp * myArray[i][k];
        }
    }

    // Обратный ход метода Гаусса
    float* newArray = new float[column];
    newArray[raw - 1] = myArray[raw - 1][raw];

    for (int i = raw - 2; i >= 0; i--) {
        newArray[i] = myArray[i][raw];

        for (int j = i + 1; j < raw; j++) newArray[i] -= myArray[i][j] * newArray[j];
    }

    // Вывод результата
    for (int i = 0; i < raw; i++) cout << newArray[i] << " ";

    cout << endl;

    delete[] myArray;
    delete[] newArray;

    t = clock() - t;

    cout << t << endl;

    return 0;
}
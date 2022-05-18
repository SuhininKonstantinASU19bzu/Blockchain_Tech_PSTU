#include <omp.h>
#include <iostream>
#include <math.h>

using namespace std;

int main() {
    omp_set_num_threads(2);

    setlocale(LC_ALL, "rus");
    system("chcp 1251");
    system("cls");

    int raw, column;

    cout << "Введите количество уравнений:" << endl << "> ";

    cin >> raw;

    cout << "Введите количество переменных:" << endl << "> ";

    cin >> column;

    float** myArray = new float* [raw];

#pragma omp parallel for
    for (int i = 0; i < raw; i++) myArray[i] = new float[column];

#pragma omp parallel for
    for (int i = 0; i < raw; i++) {
        for (int j = 0; j < column; j++) {
            cout << "Ввод элемента " << "[" << i + 1 << " , " << j + 1 << "] > ";

            cin >> myArray[i][j];
        }
    }

    //выводим массив
    cout << "Заданная матрица:" << endl;

#pragma omp parallel for
    for (int i = 0; i < raw; i++) {
        for (int j = 0; j < column; j++) cout << myArray[i][j] << " ";

        cout << endl;
    }

    cout << endl;

    // Прямой ход метода Гаусса
#pragma omp parallel for
    for (int i = 0; i < raw; i++) {
        float temp = myArray[i][i];

        for (int j = raw; j >= i; j--) myArray[i][j] /= temp;
        for (int j = i + 1; j < raw; j++) {
            temp = myArray[j][i];

            for (int k = raw; k >= i; k--) myArray[j][k] -= temp * myArray[i][k];
        }
    }

    // Обратный ход метода Гаусса
    float* newArray = new float[column];
    newArray[raw - 1] = myArray[raw - 1][raw];

#pragma omp parallel for
    for (int i = raw - 2; i >= 0; i--) {
        newArray[i] = myArray[i][raw];

        for (int j = i + 1; j < raw; j++) newArray[i] -= myArray[i][j] * newArray[j];
    }

    // Вывод результата
#pragma omp parallel for
    for (int i = 0; i < raw; i++) cout << newArray[i] << " ";

    cout << endl;

    delete[] myArray;
    delete[] newArray;

    return 0;
}
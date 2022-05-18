#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

using namespace std;

mutex myMutex1, myMutex2;

void FirstThreadInfo(int cicle) {
    lock_guard<mutex> myGuard1(myMutex1);

    this_thread::sleep_for(chrono::milliseconds(1));

    lock_guard<mutex> myGuard2(myMutex2);

    for (int i = 0; i < cicle; i++) {
        cout << "| Номер потока\t|  Счетчик цикла |" << endl;
        cout << "|\t" << this_thread::get_id() << "\t|  \t" << i << "\t |" << endl;
    }
}

void SecondThreadInfo(int cicle) {
    lock_guard<mutex> myGuard2(myMutex2);

    this_thread::sleep_for(chrono::milliseconds(1));

    lock_guard<mutex> myGuard1(myMutex1);

    for (int i = 0; i < cicle; i++) {
        cout << "| Номер потока\t|  Счетчик цикла |" << endl;
        cout << "|\t" << this_thread::get_id() << "\t|  \t" << i << "\t |" << endl;
    }
}

int main() {
    setlocale(LC_ALL, "rus");
    system("chcp 1251");
    system("cls");

	thread myThread1(FirstThreadInfo, 5);
	thread myThread2(SecondThreadInfo, 3);

    myThread1.join();
    myThread2.join();

    return 0;
}
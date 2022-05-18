#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex myMutex;

void ThreadInfo(int cicle) {
    lock_guard<mutex> myGuard(myMutex);

    for (int i = 0; i < cicle; i++) {
        cout << "| Номер потока\t|  Счетчик цикла |" << endl;
        cout << "|\t" << this_thread::get_id() << "\t|  \t" << i << "\t |" << endl;
    }
}

int main() {
    setlocale(LC_ALL, "rus");
    system("chcp 1251");
    system("cls");

    thread myThread1(ThreadInfo, 5);
    thread myThread2(ThreadInfo, 3);

    myThread1.join();
    myThread2.join();

    return 0;
}
#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

void sum(float, float, int, int, int, int*, mutex&, condition_variable&);
void subt(float, float, int, int, int, int*, mutex&, condition_variable&);
void mult(float, float, int, int, int, int*, mutex&, condition_variable&);
void divi(float, float, int, int, int, int*, mutex&, condition_variable&);

int main() {

    float a, b = 0;
    int N = 0;

    mutex mtx;
    condition_variable cv;
    int turn = 1;

    cout << "Digite um numero 'a': ";
    cin >> a;

    while (b == 0) {
        cout << "Digite um número 'b' ('b' ≠ 0): ";
        cin >> b;
    }

    while (N < 1) {
        cout << "Digite um número 'N' (N >= 1): ";
        cin >> N;
    }

    cout << "---------------------------" << endl;

    srand(1032013);

    int so_time = rand() % 10 + 1;
    int su_time = rand() % 10 + 1;
    int mu_time = rand() % 10 + 1;
    int di_time = rand() % 10 + 1;

    cout << "Tempo - So: " << so_time << "s" << endl;
    cout << "Tempo - Su: " << su_time << "s" << endl;
    cout << "Tempo - Mu: " << mu_time << "s" << endl;
    cout << "Tempo - Di: " << di_time << "s" << endl;

    cout << "---------------------------" << endl;

    thread t1(sum, a, b, so_time, N, 1, &turn, ref(mtx), ref(cv));
    thread t2(subt, a, b, su_time, N, 2, &turn, ref(mtx), ref(cv));
    thread t3(mult, a, b, mu_time, N, 3, &turn, ref(mtx), ref(cv));
    thread t4(divi, a, b, di_time, N, 4, &turn, ref(mtx), ref(cv));

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return 0;
}

void sum(float a, float b, int time, int N, int id, int* turn, mutex& mtx, condition_variable& cv) {
    for (int i = 0; i < N; i++) {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [&turn, id]() { return (*turn == id); });
        this_thread::sleep_for(chrono::seconds(time));
        cout << "N: " << i+1 << ", Op - So: " << a << " + " << b << " = " << a+b << endl;
        *turn = (*turn % 4) + 1;
        cv.notify_all();
    }
}

void subt(float a, float b, int time, int N, int id, int* turn, mutex& mtx, condition_variable& cv) {
    for (int i = 0; i < N; i++) {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [&turn, id]() { return (*turn == id); });
        this_thread::sleep_for(chrono::seconds(time));
        cout << "N: " << i+1 << ", Op - Su: " << a << " - " << b << " = " << a-b << endl;
        *turn = (*turn % 4) + 1;
        cv.notify_all();
    }
}

void mult(float a, float b, int time, int N, int id, int* turn, mutex& mtx, condition_variable& cv) {
    for (int i = 0; i < N; i++) {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [&turn, id]() { return (*turn == id); });
        this_thread::sleep_for(chrono::seconds(time));
        cout << "N: " << i+1 << ", Op - Mu: " << a << " x " << b << " = " << a*b << endl;
        *turn = (*turn % 4) + 1;
        cv.notify_all();
    }
}

void divi(float a, float b, int time, int N, int id, int* turn, mutex& mtx, condition_variable& cv) {
    for (int i = 0; i < N; i++) {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [&turn, id]() { return (*turn == id); });
        this_thread::sleep_for(chrono::seconds(time));
        cout << "N: " << i+1 << ", Op - Di: " << a << " / " << b << " = " << a/b << endl;
        *turn = (*turn % 4) + 1;
        cv.notify_all();
    }
}

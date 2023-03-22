#include <iostream>
#include <thread>
#include <semaphore.h>
#include <iostream>
#include <chrono>

using namespace std;

// declare global variables
sem_t semSum, semSub, semMult, semDiv;

// performs sum
void sum(int a, int b, int time) {
    sem_wait(&semSum);
    this_thread::sleep_for(chrono::seconds(time));
    cout << "Sum: " << a + b << endl;
    sem_post(&semSub);
}

// performs subtraction
void sub(int a, int b, int time) {
    sem_wait(&semSub);
    this_thread::sleep_for(chrono::seconds(time));
    cout << "Sub: " << a - b << endl;
    sem_post(&semMult);
}

// performs multiplication
void mult(int a, int b, int time) {
    sem_wait(&semMult);
    this_thread::sleep_for(chrono::seconds(time));
    cout << "Mult: " << a * b << endl;
    sem_post(&semDiv);
}

// performs division
void division(int a, int b, int time) {
    sem_wait(&semDiv);
    this_thread::sleep_for(chrono::seconds(time));
    cout << "Div: " << a / b << endl;
    sem_post(&semSum);
}

int main() {
    // initializes the semaphores
    sem_init(&semSum, 0, 1);
    sem_init(&semSub, 0, 0);
    sem_init(&semMult, 0, 0);
    sem_init(&semDiv, 0, 0);

    int a, b, N;
    
    cout << "Digite um numero 'a': " << endl;
    cin >> a;
    cout << "Digite um número 'b' ('b' ≠ 0): " << endl;
    cin >> b;

    while(b == 0){
        cout << "Número 'b' igual a zero!" << endl;
        cout << "Digite número 'b' ('b' ≠ 0): " << endl;
        cin >> b;
    }

    cout << "Digite um N (N >= 1): " << endl;
    cin >> N;

    while(N < 1){
        cout << "Número N menor que um!" << endl;
        cout << "Digite um N (N >= 1): " << endl;
        cin >> N;
    }

    cout << "---------------------------" << endl;

    srand(1032013);

    int sum_time = rand() % 10 + 1;
    int sub_time = rand() % 10 + 1;
    int mult_time = rand() % 10 + 1;
    int division_time = rand() % 10 + 1;

    cout << "Sum Time: " << sum_time << endl;
    cout << "Sub Time: " << sub_time << endl;
    cout << "Mult Time: " << mult_time << endl;
    cout << "Division Time: " << division_time << endl;

    cout << "---------------------------" << endl;

    for(int i = 1; i <= N; i++){
        cout << "Iteration number: " << i <<endl;

        thread t1(sum, a, b, sum_time);
        thread t2(sub, a, b, sub_time);
        thread t3(mult, a, b, mult_time);
        thread t4(division, a, b, division_time);

        t1.join();
        t2.join();
        t3.join();
        t4.join();

        cout << "---------------------------" << endl;
    }

    // destroy semaphores
    sem_destroy(&semSum);
    sem_destroy(&semSub);
    sem_destroy(&semMult);
    sem_destroy(&semDiv);

    return 0;
}

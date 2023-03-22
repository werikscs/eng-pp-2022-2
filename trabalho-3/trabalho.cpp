#include <chrono>
#include <iostream>
#include <semaphore.h>
#include <thread>

using namespace std;

void soma(float, float, int, int, sem_t *, sem_t *);
void subt(float, float, int, int, sem_t *, sem_t *);
void mult(float, float, int, int, sem_t *, sem_t *);
void divi(float, float, int, int, sem_t *, sem_t *);

int main() {
  sem_t semSo, semSu, semMu, semDi;
  
  sem_init(&semSo, 0, 1);
  sem_init(&semSu, 0, 0);
  sem_init(&semMu, 0, 0);
  sem_init(&semDi, 0, 0);

  float a, b = 0;
  int N = 0;

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

  srand(22032023);

  int so_time = rand() % 10 + 1;
  int su_time = rand() % 10 + 1;
  int mu_time = rand() % 10 + 1;
  int di_time = rand() % 10 + 1;

  cout << "Tempo - So: " << so_time << "s" << endl;
  cout << "Tempo - Su: " << su_time << "s" << endl;
  cout << "Tempo - Mu: " << mu_time << "s" << endl;
  cout << "Tempo - Di: " << di_time << "s" << endl;

  cout << "---------------------------" << endl;

  thread t1(soma, a, b, so_time, N, &semSo, &semSu);
  thread t2(subt, a, b, su_time, N, &semSu, &semMu);
  thread t3(mult, a, b, mu_time, N, &semMu, &semDi);
  thread t4(divi, a, b, di_time, N, &semDi, &semSo);

  t1.join();
  t2.join();
  t3.join();
  t4.join();

  sem_destroy(&semSo);
  sem_destroy(&semSu);
  sem_destroy(&semMu);
  sem_destroy(&semDi);

  return 0;
}

void soma(float a, float b, int time, int N, sem_t *sem_to_lock, sem_t *sem_to_unlock) {
  for (int i = 0; i < N; i++) {
    sem_wait(sem_to_lock);
    this_thread::sleep_for(chrono::seconds(time));
    cout << "N: " << i+1 << ", Op - So: " << a << " + " << b << " = " << a+b << endl;
    sem_post(sem_to_unlock);
  }
}

void subt(float a, float b, int time, int N, sem_t *sem_to_lock, sem_t *sem_to_unlock) {
  for (int i = 0; i < N; i++) {
    sem_wait(sem_to_lock);
    this_thread::sleep_for(chrono::seconds(time));
    cout << "N: " << i+1 << ", Op - Su: " << a << " - " << b << " = " << a-b << endl;
    sem_post(sem_to_unlock);
  }
}

void mult(float a, float b, int time, int N, sem_t *sem_to_lock, sem_t *sem_to_unlock) {
  for (int i = 0; i < N; i++) {
    sem_wait(sem_to_lock);
    this_thread::sleep_for(chrono::seconds(time));
    cout << "N: " << i+1 << ", Op - Mu: " << a << " x " << b << " = " << a*b << endl;
    sem_post(sem_to_unlock);
  }
}

void divi(float a, float b, int time, int N, sem_t *sem_to_lock, sem_t *sem_to_unlock) {
  for (int i = 0; i < N; i++) {
    sem_wait(sem_to_lock);
    this_thread::sleep_for(chrono::seconds(time));
    cout << "N: " << i+1 << ", Op - Di: " << a << " / " << b << " = " << a/b << endl;
    sem_post(sem_to_unlock);
  }
}
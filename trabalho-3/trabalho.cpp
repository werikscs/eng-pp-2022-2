#include <chrono>
#include <iostream>
#include <semaphore>
#include <thread>

using namespace std;

void soma(binary_semaphore *, binary_semaphore *, float, float, int, int);
void subt(binary_semaphore *, binary_semaphore *, float, float, int, int);
void mult(binary_semaphore *, binary_semaphore *, float, float, int, int);
void divi(binary_semaphore *, binary_semaphore *, float, float, int, int);

int main() {
  binary_semaphore sem_So{0};
  binary_semaphore sem_Su{0};
  binary_semaphore sem_Mu{0};
  binary_semaphore sem_Di{0};

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

  thread th_so(soma, &sem_So, &sem_Su, a, b, so_time, N);
  thread th_su(subt, &sem_Su, &sem_Mu, a, b, su_time, N);
  thread th_mu(mult, &sem_Mu, &sem_Di, a, b, mu_time, N);
  thread th_di(divi, &sem_Di, &sem_So, a, b, di_time, N);

  sem_So.release();

  th_so.join();
  th_su.join();
  th_mu.join();
  th_di.join();
}

void soma(binary_semaphore * sem_to_acquire, binary_semaphore * sem_to_release, float a, float b, int time, int N) {
  for (int i = 0; i < N; i++) {
    sem_to_acquire->acquire();
    this_thread::sleep_for(chrono::seconds(time));
    cout << "N: " << i + 1 << ", Op - So: " << a << " + " << b << " = " << a + b << endl;     
    sem_to_release->release(); 
  }
}

void subt(binary_semaphore * sem_to_acquire, binary_semaphore * sem_to_release, float a, float b, int time, int N) {
  for (int i = 0; i < N; i++) {
    sem_to_acquire->acquire();
    this_thread::sleep_for(chrono::seconds(time));
    cout << "N: " << i + 1 << ", Op - Su: " << a << " - " << b << " = " << a - b << endl;     
    sem_to_release->release(); 
  }
}

void mult(binary_semaphore * sem_to_acquire, binary_semaphore * sem_to_release, float a, float b, int time, int N) {
  for (int i = 0; i < N; i++) {
    sem_to_acquire->acquire();
    this_thread::sleep_for(chrono::seconds(time));
    cout << "N: " << i + 1 << ", Op - Mu: " << a << " x " << b << " = " << a * b << endl;
    sem_to_release->release(); 
  }
}

void divi(binary_semaphore * sem_to_acquire, binary_semaphore * sem_to_release, float a, float b, int time, int N) {
  for (int i = 0; i < N; i++) {
    sem_to_acquire->acquire();
    this_thread::sleep_for(chrono::seconds(time));
    cout << "N: " << i + 1 << ", Op - Di: " << a << " / " << b << " = " << a / b << endl;
    sem_to_release->release(); 
  }
}

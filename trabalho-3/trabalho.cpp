#include <chrono>
#include <iostream>
#include <semaphore>
#include <thread>

using namespace std;

void soma(float a, float b, int time, int N, std::counting_semaphore<1> &sem_to_lock, std::counting_semaphore<1> &sem_to_unlock)
{
  for (int i = 0; i < N; i++)
  {
    sem_to_lock.acquire();
    this_thread::sleep_for(chrono::seconds(time));
    cout << "N: " << i + 1 << ", Op - So: " << a << " + " << b << " = " << a + b << endl;
    sem_to_unlock.release();
  }
}

void subt(float a, float b, int time, int N, std::counting_semaphore<1> &sem_to_lock, std::counting_semaphore<1> &sem_to_unlock)
{
  for (int i = 0; i < N; i++)
  {
    sem_to_lock.acquire();
    this_thread::sleep_for(chrono::seconds(time));
    cout << "N: " << i + 1 << ", Op - Su: " << a << " - " << b << " = " << a - b << endl;
    sem_to_unlock.release();
  }
}

void mult(float a, float b, int time, int N, std::counting_semaphore<1> &sem_to_lock, std::counting_semaphore<1> &sem_to_unlock)
{
  for (int i = 0; i < N; i++)
  {
    sem_to_lock.acquire();
    this_thread::sleep_for(chrono::seconds(time));
    cout << "N: " << i + 1 << ", Op - Mu: " << a << " x " << b << " = " << a * b << endl;
    sem_to_unlock.release();
  }
}

void divi(float a, float b, int time, int N, std::counting_semaphore<1> &sem_to_lock, std::counting_semaphore<1> &sem_to_unlock)
{
  for (int i = 0; i < N; i++)
  {
    sem_to_lock.acquire();
    this_thread::sleep_for(chrono::seconds(time));
    cout << "N: " << i + 1 << ", Op - Di: " << a << " / " << b << " = " << a / b << endl;
    sem_to_unlock.release();
  }
}

int main()
{
  counting_semaphore<1> semSo(1), semSu(1), semMu(1), semDi(1);

  float a, b = 0;
  int N = 0;

  cout << "Digite um numero 'a': ";
  cin >> a;

  while (b == 0)
  {
    cout << "Digite um número 'b' ('b' ≠ 0): ";
    cin >> b;
  }

  while (N < 1)
  {
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

  thread t1(soma, a, b, so_time, N, std::ref(semSo), std::ref(semSu));
  thread t2(subt, a, b, su_time, N, std::ref(semSu), std::ref(semMu));
  thread t3(mult, a, b, mu_time, N, std::ref(semMu), std::ref(semDi));
  thread t4(divi, a, b, di_time, N, std::ref(semDi), std::ref(semSo));

  t1.join();
  t2.join();
  t3.join();
  t4.join();

  return 0;
}

// Davi Carvalho, Wériks da Conceição Santos, Israel David Caetano

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

using namespace std;

void print_square_matrix(const vector<vector<int>>& matrix, int n);

void resolve_linear_system(const vector<vector<int>>& matrix, vector<double>& x,
                           vector<int>& b, int n, double& sum, int& turn,
                           int& i, mutex& mtx, condition_variable& cv);

void calculate_sum(const vector<vector<int>>& matrix, vector<int>& b,
                   vector<double>& x, int n, double& sum, int& turn, int& i,
                   mutex& mtx, condition_variable& cv);

int main() {
  mutex mtx;
  condition_variable cv;
  int turn = 1;

  int n = 3;
  int i = n - 1;
  double sum = 0;

  vector<vector<int>> matrix = {
      {3, 4, 5},
      {0, 3, 4},
      {0, 0, 3},
  };

  vector<int> b;
  b.assign({2, 2, 2});

  vector<double> x(n, 0);

  print_square_matrix(matrix, n);

  thread t1(resolve_linear_system, matrix, ref(x), ref(b), n, ref(sum),
            ref(turn), ref(i), ref(mtx), ref(cv));
  thread t2(calculate_sum, matrix, ref(b), ref(x), n, ref(sum), ref(turn),
            ref(i), ref(mtx), ref(cv));

  t1.join();
  t2.join();

  cout << "\nResultado: \n";

  for (int i = 0; i < n; i++) {
    cout << x[i] << " ";
  }

  return 0;
}

void print_square_matrix(const vector<vector<int>>& matrix, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << matrix[i][j] << " ";
    }
    cout << endl;
  }
}

void resolve_linear_system(const vector<vector<int>>& matrix, vector<double>& x,
                           vector<int>& b, int n, double& sum, int& turn,
                           int& i, mutex& mtx, condition_variable& cv) {
  for (int p = n - 1; p >= 0; p--) {
    unique_lock<mutex> lock(mtx);
    cv.wait(lock, [&turn]() { return (turn == 1); });

    i = p;     // i recebe a iteração atual
    turn = 2;  // seta a vez para calculate_sum

    cv.notify_one();  // notifica calculate_sum
    cv.wait(lock, [&turn]() {
      return (turn == 1);
    });  // espera calculate_sum terminar

    x[p] =
        (b[p] - sum) /
        static_cast<double>(
            matrix[p][p]);  // seta o resultado referente à linha atual (p) em x
  }
}

void calculate_sum(const vector<vector<int>>& matrix, vector<int>& b,
                   vector<double>& x, int n, double& sum, int& turn, int& i,
                   mutex& mtx, condition_variable& cv) {
  for (int p = 0; p < n; p++) {
    unique_lock<mutex> lock(mtx);
    cv.wait(lock, [&turn]() { return (turn == 2); });

    double local_sum = 0;  // soma local sempre zerada no começo do somatório de
                           // cada linha da matriz
    for (int j = i + 1; j < n; j++) {
      local_sum += matrix[i][j] * x[j];
    }

    sum = local_sum;

    turn = 1;  // seta a vez para resolve_linear_system

    cv.notify_one();  // notifica resolve_linear_system
  }
}

// Davi Carvalho, Wériks da Conceição Santos, Israel David Caetano

#include <iostream>

using namespace std;

int calculateRecursiveExponential(int a, int b);

int main() {
  int a, b;
  int result;

  do {
    cout << "\nEnter a (must be non-zero): ";
    cin >> a;

    cout << "\nEnter b (must be greater than or equal to zero): ";
    cin >> b;

  } while (a == 0 || b < 0);

  result = calculateRecursiveExponential(a, b);

  cout << result << endl;

  return 0;
}

int calculateRecursiveExponential(int a, int b) {
  if (b == 0)
    return 1;
  else
    return a * calculateRecursiveExponential(a, b - 1);
}
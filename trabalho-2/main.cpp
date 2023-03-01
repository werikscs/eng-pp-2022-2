// Davi Carvalho, Wériks da Conceição Santos, Israel David Caetano

#include <stdlib.h>
#include <unistd.h>

#include <iostream>
#include <thread>

using namespace std;

void printPreSleep(string operacao, float value, int time) {
  cout << "Eu sou a Thread " << operacao << " (" << value << ") e vou dormir por " << time << " segundos!" << endl;
}

void printPosSleep(string operacao, float value, int time) {
  cout << "Eu sou a Thread " << operacao << " (" << value << "). Já se passaram " << time << " segundos, então terminei!" << endl;
}

void subtrair(float a, float b, int time) {
  printPreSleep("SUBTRACAO", a - b, time);
  sleep(time);
  printPosSleep("SUBTRACAO", a - b, time);
}
void somar(float a, float b, int time) {
  printPreSleep("SOMA", a + b, time);
  sleep(time);
  printPosSleep("SOMA", a + b, time);
}
void multiplicar(float a, float b, int time) {
  printPreSleep("MULTIPLICACAO", a * b, time);
  sleep(time);
  printPosSleep("MULTIPLICACAO", a * b, time);
}
void dividir(float a, float b, int time) {
  if (b == 0)
    throw "Deu ruim";
  printPreSleep("DIVISAO", a / b, time);
  sleep(time);
  printPosSleep("DIVISAO", a / b, time);
}

int main() {
  float a, b;

  cout << "Digite um número: ";
  cin >> a;
  cout << "Digite outro número (número ≠ 0): ";
  cin >> b;

  thread t_soma(subtrair, a, b, rand() % 20 + 1);
  thread t_subtracao(somar, a, b, rand() % 20 + 1);
  thread t_multiplicacao(multiplicar, a, b, rand() % 20 + 1);
  thread t_divisao(dividir, a, b, rand() % 20 + 1);

  t_soma.join();
  t_subtracao.join();
  t_multiplicacao.join();
  t_divisao.join();

  return 0;
}
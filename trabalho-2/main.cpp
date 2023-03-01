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
  const float operacao = a - b;
  printPreSleep("SUBTRACAO", operacao, time);
  sleep(time);
  printPosSleep("SUBTRACAO", operacao, time);
}
void somar(float a, float b, int time) {
  const float operacao = a + b;
  printPreSleep("SOMA", operacao, time);
  sleep(time);
  printPosSleep("SOMA", operacao, time);
}
void multiplicar(float a, float b, int time) {
  const float operacao = a * b;
  printPreSleep("MULTIPLICACAO", operacao, time);
  sleep(time);
  printPosSleep("MULTIPLICACAO", operacao, time);
}
void dividir(float a, float b, int time) {
  if (b == 0)
    throw "Deu ruim";

  const float operacao = a / b;
  printPreSleep("DIVISAO", operacao, time);
  sleep(time);
  printPosSleep("DIVISAO", operacao, time);
}

int main() {
  float a, b;

  cout << "Digite um número: ";
  cin >> a;
  cout << "Digite outro número (número ≠ 0): ";
  cin >> b;

  srand(1032013);
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
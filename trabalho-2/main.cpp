// Davi Carvalho, Wériks da Conceição Santos, Israel David Caetano

#include <cstdlib>
#include <chrono>
#include <iostream>
#include <thread>
#include <cmath>

using namespace std;

void printPreSleep(string, float, int);
void printPosSleep(string, float, int);
void subtrair(float, float, int);
void somar(float, float, int);
void multiplicar(float, float, int);
void dividir(float, float, int);

int main() {
  float a, b;

  cout << "Digite um número: ";
  cin >> a;
  cout << "Digite outro número (número ≠ 0): ";
  cin >> b;

  srand(1032013);

  int soma_time = rand() % 20 + 1;
  int subtracao_time = rand() % 20 + 1;
  int multiplicacao_time = rand() % 20 + 1;
  int divisao_time = rand() % 20 + 1;

  thread thread_soma(subtrair, a, b, soma_time);
  thread thread_subtracao(somar, a, b, subtracao_time);
  thread thread_multiplicacao(multiplicar, a, b, multiplicacao_time);
  thread thread_divisao(dividir, a, b, divisao_time);
  
  thread_soma.join();
  thread_subtracao.join();
  thread_multiplicacao.join();
  thread_divisao.join();

  return 0;
}

void printPreSleep(string operacao, float value, int time) {
  string msg = "Eu sou a Thread " + operacao + " (" + to_string(value) +
    ") e vou dormir por " + to_string(time) + " segundos!\n";
  cout << msg;
}

void printPosSleep(string operacao, float value, int time) {
  string msg = "Eu sou a Thread " + operacao + " (" + to_string(value) + 
    "). Já se passaram " + to_string(time) + " segundos, então terminei!\n";
  cout << msg;
}

void subtrair(float a, float b, int time) {
  const float value = a - b;
  const string operacao = "SUBTRACAO";
  
  printPreSleep(operacao, value, time);
  this_thread::sleep_for(chrono::seconds(time));
  printPosSleep(operacao, value, time);
}

void somar(float a, float b, int time) {
  const float value = a + b;
  const string operacao = "SOMA";
  
  printPreSleep(operacao, value, time);
  this_thread::sleep_for(chrono::seconds(time));
  printPosSleep(operacao, value, time);
}

void multiplicar(float a, float b, int time) {
  const float value = a * b;
  const string operacao = "MULTIPLICACAO";
  
  printPreSleep(operacao, value, time);
  this_thread::sleep_for(chrono::seconds(time));
  printPosSleep(operacao, value, time);
}

void dividir(float a, float b, int time) {
  if (b == 0) throw "Deu ruim";

  const float value = a / b;
  const string operacao = "DIVISAO";
  
  printPreSleep(operacao, value, time);
  this_thread::sleep_for(chrono::seconds(time));
  printPosSleep(operacao, value, time);
}

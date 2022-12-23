// Davi Carvalho, Wériks da Conceição Santos, Israel David Caetano

/* Desenvolver um algoritmo que faz uso de duas Threads (além da Thread
principal), onde uma tem que imprimir na tela “Feliz Natal” e a outra “Feliz Ano
Novo” */

#include <iostream>
#include <thread>

using namespace std;

void printText(string text) { cout << text << endl; }

int main() {
  // threads call printText with the argument
  std::thread t1(printText, "Feliz Natal");
  std::thread t1(printText, "Feliz Ano Novo");

  // synchronize threads
  t1.join();
  t2.join();

  return 0;
}
// gcc main.cpp -lstdc++ -o main && ./main

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// fill vector with random numbers
void fillVectorWithRandomNumbers(int * vector, int vectorSize);
// sort vector by non-ascending order
void sortVectorNonAscending(int * vector, int vectorSize);
// print vector before and after sorting
void printVector(int * vector, int vectorSize);

int main() {
  int vectorSize = 30;
	int vector[vectorSize] = {};
  
  // filling
  fillVectorWithRandomNumbers(vector, vectorSize);
  // before sorting
  printVector(vector, vectorSize);
  // sorting
  sortVectorNonAscending(vector, vectorSize);
  // after sorting
  printVector(vector, vectorSize);
}

void fillVectorWithRandomNumbers(int * vector, int vectorSize){
  srand(time(NULL));

  for(int i=1; i<= vectorSize; i++)
    vector[i-1] = 1 + (rand() % vectorSize);
}

void sortVectorNonAscending(int * vector, int vectorSize) {
  int i, key, j;

  for(i = 1; i < vectorSize; i++) {
    key = vector[i];
    j = i - 1;

    while(j >= 0 && vector[j] > key) {
      vector[j + 1] = vector[j];
      j = j - 1;
    }

    vector[j + 1] = key;
  }
}

void printVector(int * vector, int vectorSize) {
  for(int i = 0; i < vectorSize; i++)
    cout << vector[i] << " ";
  
  cout << endl;
}
// gcc main.cpp -lstdc++ -o main && ./main

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void fillVectorWithRandomNumbers(int *, int, int);
int findLargestValueVector(int, int *, int, int);

int main() {

  int vectorSize = 50;
	int vector[vectorSize] = {};
  int maxNum = 100;

  int largestValue;
  
  fillVectorWithRandomNumbers(vector, vectorSize, maxNum);

  cout << "Vector: ";
  for(int i=0; i<vectorSize; i++)
    cout << vector[i] << " ";

  cout << endl;

  largestValue = findLargestValueVector(vector[0], vector, vectorSize, 1);

  cout << "Largest value: " << largestValue << endl;

  return 0;
}

void fillVectorWithRandomNumbers(int * vector, int vectorSize, int maxNum) {
  srand(time(NULL));

  for(int i=0; i<vectorSize; i++) {
    vector[i] = 1 + (rand() % maxNum);
  }
}

int findLargestValueVector(int largestNum, int * vector, int vectorSize, int index) {
  if(index == vectorSize - 1)
    return largestNum;
  else
    if(vector[index] > largestNum)
      return findLargestValueVector(vector[index], vector, vectorSize, index + 1);
    else
      return findLargestValueVector(largestNum, vector, vectorSize, index + 1);
}   
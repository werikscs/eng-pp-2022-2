// gcc main.cpp -lstdc++ -o main && ./main

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

// fill vector with random numbers
void fillVectorWithRandomNumbers(vector<int>& vector, int maxNum);
// sort vector by non-ascending order
void sortVectorNonAscending(vector<int>& vector);
// print vector before and after sorting
void printVector(vector<int>& vector);

int main() {
  int vectorSize = 30;
  int maxNum = 30;
	vector<int> vector(vectorSize);
  
  // filling
  fillVectorWithRandomNumbers(vector, maxNum);
  // before sorting
  printVector(vector);
  // sorting
  sortVectorNonAscending(vector);
  // after sorting
  printVector(vector);
}

void fillVectorWithRandomNumbers(vector<int>& vector, int maxNum) {
  srand(time(NULL));

  for(int i = 0; i < vector.size(); i++)
    vector[i] = (rand() % maxNum) + 1;
}

void sortVectorNonAscending(vector<int>& vector) {
  int i, j, maxPosition, aux;

  for(i = 0; i < vector.size(); i++) {

    maxPosition = i;

    // loops through the rest of the vector and gets the position of the major value
    for(int j = i; j < vector.size(); j++){
        if(vector[j] >= vector[maxPosition]){
            maxPosition = j;
        }
    }

    // swaps values
    aux = vector[i];
    vector[i] = vector[maxPosition];
    vector[maxPosition] = aux;
  }
}

void printVector(vector<int>& vector) {
  for(int i = 0; i < vector.size(); i++){
    cout << vector[i] << " ";
  }

  cout << endl;
}
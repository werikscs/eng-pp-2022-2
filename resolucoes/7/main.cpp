// Davi Carvalho, Wériks da Conceição Santos, Israel David Caetano

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

void fillVectorWithRandomNumbers(vector<int>& vector, int);
int findLargestValueVector(vector<int>& vector, int);

int main() {

  int vectorSize = 50;
	vector<int> vector(vectorSize);
  int maxNum = 100;

  int largestValue;
  
  fillVectorWithRandomNumbers(vector, maxNum);

  cout << "Vector: ";
  for(int i = 0; i < vector.size(); i++)
    cout << vector[i] << " ";

  cout << endl;

  largestValue = findLargestValueVector(vector, 0);

  cout << "Largest value: " << largestValue << endl;

  return 0;
}

void fillVectorWithRandomNumbers(vector<int>& vector, int maxNum) {
  srand(time(NULL));

  for(int i = 0; i < vector.size(); i++) {
    vector[i] = 1 + (rand() % maxNum);
  }
}

int findLargestValueVector(vector<int>& vector, int index) {

  // returns the value when it reaches the end of the vector
  if(index == (vector.size() - 1))
    return vector[index];

  else{    

    int largestValue = findLargestValueVector(vector, index+1);

    // if current value is greater than the returned value of the call, returns
    // current value to the previous call of the function
    if(vector[index] >= largestValue){
      return vector[index];
    }
    else{
      return largestValue;
    }
  }
}   
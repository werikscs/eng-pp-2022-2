// Davi Carvalho, Wériks da Conceição Santos, Israel David Caetano

#include <math.h>

#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

// fills a matrix with random numbers from 1 to maxNum
void fillMatrix(vector<vector<int>>& matrix, int maxNum) {
  srand(time(0));

  for (int i = 0; i < matrix.size(); i++) {
    for (int j = 0; j < matrix[i].size(); j++) {
      matrix[i][j] = (rand() % maxNum) + 1;
    }
  }
}

// show the matrix that was passed on the terminal's scream
void showMatrix(vector<vector<int>>& matrix) {
  for (int i = 0; i < matrix.size(); i++) {
    for (int j = 0; j < matrix[i].size(); j++) {
      cout << matrix[i][j] << "\t";
    }

    cout << "\n";
  }
}

bool checkMatrix(vector<vector<int>>& matrix) {
  int min = 0;
  int max = 0;
  int sumColumns = 0;
  int productLines = 1;

  cout << "Sums of the column values: ";
  for (int j = 0; j < matrix[0].size(); j++) {
    for (int i = 0; i < matrix.size(); i++) {
      // increments the sum of the columns with absolute values
      sumColumns += fabs(matrix[i][j]);
    }

    cout << sumColumns << " - ";

    // check if sum was minor than 'min' or 'min' wasn't incremented yet
    if (sumColumns < min || min == 0) {
      min = sumColumns;
    }

    // erase number from the variable for the next loop
    sumColumns = 0;
  }

  cout << "\nProducts of the row values:";
  for (int i = 0; i < matrix.size(); i++) {
    for (int j = 0; j < matrix[0].size(); j++) {
      // increments the produtct with values from the rows
      productLines *= matrix[i][j];
    }

    cout << productLines << " - ";

    // check if product was greater than 'max'
    if (productLines > max) {
      max = productLines;
    }

    // erase number from the variable for the next loop
    productLines = 1;
  }

  // print values for easy checking
  cout << "\n";
  cout << "Min sum: " << min << "\n";
  cout << "Max product: " << max << "\n";

  if (min <= max) {
    return true;
  } else {
    return false;
  }
}

int main() {
  int n = 4;
  int m = 5;
  int maxNum = 21;
  vector<vector<int>> matrix(m, vector<int>(n));

  fillMatrix(matrix, maxNum);

  showMatrix(matrix);

  if (checkMatrix(matrix)) {
    cout << "Condicao Satisfeita";
  } else {
    cout << "Condicao Nao Satisfeita";
  }

  return 0;
}
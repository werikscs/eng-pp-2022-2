// Davi Carvalho, Wériks da Conceição Santos, Israel David Caetano

#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

// fills a matrix with random numbers from 0 to maxNum
void fillMatrix(vector<vector<int>>& matrix, int maxNum) {
  srand(time(0));

  for (int i = 0; i < matrix.size(); i++) {
    for (int j = 0; j < matrix[i].size(); j++) {
      matrix[i][j] = rand() % maxNum;
    }
  }
}

// transposes a given matrix and put the values on transposedMatrix
void transposeMatrix(vector<vector<int>>& matrix,
                     vector<vector<int>>& transposedMatrix) {
  for (int i = 0; i < matrix.size(); i++) {
    for (int j = 0; j < matrix[0].size(); j++) {
      transposedMatrix[j][i] = matrix[i][j];
    }
  }
}

// multiply matrix and transposedMatrix and puts values on productMatrix
void multiplyMatrix(vector<vector<int>>& matrix,
                    vector<vector<int>>& transposedMatrix,
                    vector<vector<int>>& productMatrix) {
  int sum = 0;

  for (int i = 0; i < matrix.size(); i++) {
    for (int j = 0; j < matrix[0].size(); j++) {
      for (int k = 0; k < transposedMatrix.size(); k++) {
        // will stay on matrix's row and loop through the columns of the row
        // until all the collumns and rows of transposedMatrix are multiplied
        sum += matrix[i][k] * transposedMatrix[k][j];
      }

      productMatrix[i][j] = sum;
      sum = 0;
    }
  }
}

// fills identityMatrix with proper values
void generateIdentityMatrix(vector<vector<int>>& identityMatrix) {
  for (int i = 0; i < identityMatrix.size(); i++) {
    for (int j = 0; j < identityMatrix.size(); j++) {
      if (j == i) {
        identityMatrix[i][j] = 1;
      } else {
        identityMatrix[i][j] = 0;
      }
    }
  }
}

// verify if the given matrix is orthogonal
bool verifyOrthogonal(vector<vector<int>>& matrix) {
  vector<vector<int>> identityMatrix(matrix.size(), vector<int>(matrix.size()));

  generateIdentityMatrix(identityMatrix);

  for (int i = 0; i < matrix.size(); i++) {
    for (int j = 0; j < matrix[i].size(); j++) {
      if (matrix[i][j] != identityMatrix[i][j]) {
        return false;
      }
    }
  }

  return true;
}

// show the matrix that was passed on the terminal's scream
void showMatrix(vector<vector<int>>& matrix) {
  for (int i = 0; i < matrix.size(); i++) {
    for (int j = 0; j < matrix[i].size(); j++) {
      cout << matrix[i][j] << " ";
    }

    cout << "\n";
  }
}

int main() {
  int matrixOrder = 4;
  int maxNum = 30;
  vector<vector<int>> matrix(matrixOrder, vector<int>(matrixOrder));
  vector<vector<int>> transposedMatrix(matrixOrder, vector<int>(matrixOrder));
  vector<vector<int>> productMatrix(matrixOrder, vector<int>(matrixOrder));

  fillMatrix(matrix, maxNum);

  // generateIdentityMatrix(matrix);

  cout << "Original Matrix\n";
  showMatrix(matrix);

  transposeMatrix(matrix, transposedMatrix);

  cout << "Transposed Matrix\n";
  showMatrix(transposedMatrix);

  multiplyMatrix(matrix, transposedMatrix, productMatrix);

  cout << "Product Matrix\n";
  showMatrix(productMatrix);

  if (verifyOrthogonal(productMatrix)) {
    cout << "\nOriginal matrix is orthogonal\n";
  } else {
    cout << "\nOriginal matrix is NOT orthogonal\n";
  }

  return 0;
}

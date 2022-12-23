// Davi Carvalho, Wériks da Conceição Santos, Israel David Caetano

#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

void fillVector(vector<int>& vector) {
  int value;
  srand(time(0));

  // get only even numbers
  cout << "Type in " << vector.size() / 2 << " even numbers:\n";
  for (int i = 0; i < vector.size() / 2; i++) {
    cout << i + 1 << "/" << vector.size() / 2 << ":";
    cin >> value;

    if (value % 2 != 0) {
      cout << "Input is not an even number!\n";
      // if value is invalid (odd number), undo the increment of 'i'
      i--;
    } else {
      int j = 0;

      // loop that will run until it generates a position of the vector
      // that is not already taken (where value is not 0)
      do {
        j = rand() % vector.size();
      } while (vector[j] != 0);

      // puts user input on the random generated position
      vector[j] = value;
    }
  }

  // get only odd numbers
  cout << "Type in " << vector.size() / 2 << " odd numbers:\n";
  for (int i = 0; i < vector.size() / 2; i++) {
    cout << i + 1 << "/" << vector.size() / 2 << ":";
    cin >> value;

    // if value is invalid (even number), undo the increment of 'i'
    if (value % 2 == 0) {
      cout << "Input is not an odd number!\n";
      i--;
    } else {
      int j = 0;

      // loop that will run until it generates a position of the vector
      // that is not already taken (where value is not 0)
      do {
        j = rand() % vector.size();
      } while (vector[j] != 0);

      // puts user input on the random generated position
      vector[j] = value;
    }
  }
}

// organizes vector where even numbers are placed on odd positions and vice
// versa
void organizeVector(vector<int>& vector) {
  for (int i = 0; i < vector.size(); i++) {
    int aux;

    // checks if value and position are even.
    if (vector[i] % 2 == 0 && i % 2 == 0) {
      aux = vector[i];

      // if they are even, loop through entire array from next position relative
      // to 'i' position
      for (int j = i + 1; j < vector.size(); j++) {
        // if position and value are odd, switch the value
        // to the even position found at 'i' position and breaks the for loop
        if (j % 2 == 1 && (vector[j] % 2 == 1)) {
          vector[i] = vector[j];
          vector[j] = aux;
          break;
        }
      }
    }

    // checks if value and position are even.
    if (vector[i] % 2 == 1 && i % 2 == 1) {
      aux = vector[i];

      // if they are odd, loop through entire array from next position relative
      // to 'i' position
      for (int j = i + 1; j < vector.size(); j++) {
        // if position and value are even, switch the value
        // to the odd position found at 'i' position and breaks the for loop
        if (j % 2 == 0 && (vector[j] % 2 == 0)) {
          vector[i] = vector[j];
          vector[j] = aux;
          break;
        }
      }
    }
  }
}

void showVector(vector<int>& vector) {
  for (int i = 0; i < vector.size(); i++) {
    cout << vector[i] << " ";
  }
}

int main() {
  int vectorSize = 20;

  vector<int> vector(vectorSize);

  fillVector(vector);

  cout << "Vector before organization:";
  showVector(vector);

  organizeVector(vector);

  cout << "\n\nVector after organization:";
  showVector(vector);
}

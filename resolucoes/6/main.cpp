// Davi Carvalho, Wériks da Conceição Santos, Israel David Caetano

#include <iostream>
#include <vector>

using namespace std;

// print vector on the screen
void showVector(vector<int>&vector){
    for(int i = 0; i < vector.size(); i++){
        cout << vector[i] << " ";
    }
}

int checkCompositeNumber(int number){
    int dividers = 0;

    // for loop counts how many natural dividers the number has
    for(int i = 1; i <= number; i++){
        if(number % i == 0){
            dividers++;
        }
    }

    if(dividers == 2){
        return 0;
    }
    else{
        return 1;
    }
}


// puts composite numbers on the begginning of the vector
int organizeVector(vector<int>& vector, int i){

    // checks if 'i' reached the end of the vector
    if(i < (vector.size()-1)){

        // if vector[i] is not a composite number, will call
        // the function recursively until it finds a composite number,
        // which position will be returned at the end of the function.
        // then swaps the positions with the help of an auxiliar variable
        if(!checkCompositeNumber(vector[i])){
            int j = organizeVector(vector, i+1);
            int aux = vector[i];
            vector[i] = vector[j];
            vector[j] = aux;

            // call the function again to do the same for the rest of the numbers,
            // until it reaches the end of the vector
            organizeVector(vector, i+1);
            
        }
        else{
            // if number is a composite number, call the function for the next number,
            // but don't swap the numbers, obviously
            organizeVector(vector, i+1);
        }
    }

    return i;
}

// ask user to input numbers
void fillVector(vector<int>& vector){
    int value;

    cout << "Type in natural numbers greater than 1\n";
    for(int i = 0; i < vector.size(); i++){
        cout << i+1 << "/" << vector.size() << "\n";

        cin >> value;

        // check if input was valid
        while(value <= 1){
            cout << "Invalid number!\n";
            i--;
        }

        vector[i] = value;
    }
}

int main() {
    int vectorSize = 20;
    vector<int> vector(vectorSize); //= {5, 3, 7, 8, 12, 7, 21, 9, 31, 43, 56};

    fillVector(vector);

    cout << "Organizando vetor\n";

    organizeVector(vector, 0);
    
    showVector(vector);
}

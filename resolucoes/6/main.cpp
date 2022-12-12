// gcc main.cpp -lstdc++ -o main && ./main

#include <iostream>
#include <vector>

using namespace std;

void showVector(vector<int>&vector){
    for(int i = 0; i < vector.size(); i++){
        cout << vector[i] << " ";
    }
}

int checkCompositeNumber(int number){
    int dividers = 0;

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

int organizeVector(vector<int>& vector, int i){
    if(i < vector.size()){
        if(!checkCompositeNumber(vector[i])){
            int j = organizeVector(vector, i+1);
            int aux = vector[i];
            vector[i] = vector[j];
            vector[j] = aux;

            showVector(vector);
                
            cout << "\n";
            
        }
    }

    return i;
}

void fillVector(vector<int>& vector){
    int value;

    cout << "Type in natural numbers greater than 1\n";
    for(int i = 0; i < vector.size(); i++){
        cout << i+1 << "/" << vector.size() << "\n";

        cin >> value;

        while(value <= 1){
            cout << "Invalid number!\n";
            i--;
        }

        vector[i] = value;
    }
}

int main() {
    int vectorSize = 3;
    vector<int> vector = {5, 3, 7, 8, 12, 7, 21, 9, 31, 43, 56};

    //fillVector(vector);

    cout << "Organizando vetor\n";

    organizeVector(vector, 0);
    
    showVector(vector);
    
}

// gcc main.cpp -lstdc++ -o main && ./main

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

void fillMatrix(std::vector<std::vector<int>>& matrix, int maxNum){
    srand(time(0));

    for(int i = 0; i < matrix.size(); i++){
       for(int j = 0; j < matrix[i].size(); j++){
            matrix[i][j] = rand() % maxNum;
        } 
    }
}

void transposeMatrix(std::vector<std::vector<int>>& matrix,
                     std::vector<std::vector<int>>& transposedMatrix){
   
    for(int i = 0; i < matrix.size(); i++){
       for(int j = 0; j < matrix[0].size(); j++){
            transposedMatrix[j][i] = matrix[i][j];
        } 
    }
}

void multiplyMatrix(std::vector<std::vector<int>>& matrix,
                    std::vector<std::vector<int>>& transposedMatrix,
                    std::vector<std::vector<int>>& productMatrix){
    
    int sum = 0;

    for(int i = 0; i < matrix.size(); i++){
       for(int j = 0; j < matrix[0].size(); j++){
            for(int k = 0; k < transposedMatrix.size(); k++){
                sum += matrix[i][k] * transposedMatrix[k][j];
            }

            productMatrix[i][j] = sum;
            sum = 0;
        } 
        
    }
}

void generateIdentityMatrix(std::vector<std::vector<int>>& identityMatrix){
    for(int i = 0; i < identityMatrix.size(); i++){
        for(int j = 0; j < identityMatrix.size(); j++){
            if(j == i){
                identityMatrix[i][j] = 1;
            }
            else{
                identityMatrix[i][j] = 0;
            }
        } 
    }
}

bool verifyOrthogonal(std::vector<std::vector<int>>& matrix){
    std::vector<std::vector<int>> identityMatrix(matrix.size(), std::vector<int>(matrix.size()));

    generateIdentityMatrix(identityMatrix);

    for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix[i].size(); j++){
            if(matrix[i][j] != identityMatrix[i][j]){
                return false;
            }
        } 
    }

    return true;
}

void showMatrix(std::vector<std::vector<int>>& matrix){

    for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix[i].size(); j++){
            cout << matrix[i][j] << " ";
        } 

        cout << "\n";
    }
}

int main() {
    int matrixOrder = 4;
    int maxNum = 30;
    std::vector<std::vector<int>> matrix(matrixOrder, std::vector<int>(matrixOrder));
    std::vector<std::vector<int>> transposedMatrix(matrixOrder, std::vector<int>(matrixOrder));
    std::vector<std::vector<int>> productMatrix(matrixOrder, std::vector<int>(matrixOrder));

    fillMatrix(matrix, maxNum);  
    
    //generateIdentityMatrix(matrix);

    cout << "Original Matrix\n";
    showMatrix(matrix);
    
    transposeMatrix(matrix, transposedMatrix); 
     
    cout << "Transposed Matrix\n";
    showMatrix(transposedMatrix);

    multiplyMatrix(matrix, transposedMatrix, productMatrix);

    cout << "Product Matrix\n";
    showMatrix(productMatrix);

    if(verifyOrthogonal(productMatrix)){
        cout << "\nOriginal matrix is orthogonal\n";
    }
    else{
        cout << "\nOriginal matrix is NOT orthogonal\n";
    }

    return 0;
}


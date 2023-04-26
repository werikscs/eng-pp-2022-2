// Davi Carvalho, Wériks da Conceição Santos, Israel David Caetano

#include <iostream>
#include <vector> 
#include <thread>
#include <ctime>
#include <mutex>
#include <condition_variable> 

using namespace std;

void print_matrix(vector<vector<int>>& matrix, int n);
void generate_matrix(vector<vector<int>>& matrix, int n);

void multiply_matrices(vector<vector<int>>& matrix3, int n, int& result, int& turn, 
    int& i, int& j, mutex& mtx, condition_variable& cv);

void calculate_line_result(vector<vector<int>>& matrix1, vector<vector<int>>& matrix2,
    int n, int& result, int& turn, int& i, int& j, mutex& mtx, condition_variable& cv);

int main() {
    mutex mtx;
    condition_variable cv;
    int turn = 1;

    srand((unsigned)time(0)); 

    int n = 3;
    int i = 0;
    int j = 0;
    int result = 0;

    vector<vector<int>> matrix1(n, vector<int>(n));
    vector<vector<int>> matrix2(n, vector<int>(n));
    vector<vector<int>> matrix3(n, vector<int>(n));

    generate_matrix(matrix1, n);
    generate_matrix(matrix2, n);

    cout << "Matrix 1: \n";
    print_matrix(matrix1, n);
    cout << "Matrix 2: \n";
    print_matrix(matrix2, n);

    thread t1(multiply_matrices, ref(matrix3), n, ref(result), ref(turn), ref(i), ref(j), ref(mtx), ref(cv));
    thread t2(calculate_line_result, ref(matrix1), ref(matrix2), n, ref(result), ref(turn), ref(i), ref(j), ref(mtx), ref(cv));

    t1.join();
    t2.join();

    cout << "Matrix 3 (Multiplication of 1 and 2): \n";
    print_matrix(matrix3, n);
}

void generate_matrix(vector<vector<int>>& matrix, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            matrix[i][j] = (rand()%10)+1;
        }
    }
}

void print_matrix(vector<vector<int>>& matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void multiply_matrices(vector<vector<int>>& matrix3, int n, int& result, 
    int& turn, int& i, int& j, mutex& mtx, condition_variable& cv){

    for(int k = 0; k < n; k++){
        for(int l = 0; l < n; l++){
            unique_lock<mutex> lock(mtx);
            cv.wait(lock, [&turn]() { return (turn == 1); });  
            i = k;
            j = l;
            turn = 2; 

            cv.notify_one(); 
            cv.wait(lock, [&turn]() { return (turn == 1); }); 

            matrix3[k][l] = result;
        }
    }
}

void calculate_line_result(vector<vector<int>>& matrix1, vector<vector<int>>& matrix2, 
    int n, int& result, int& turn, int& i, int& j, mutex& mtx, condition_variable& cv){
        
    for (int p = 0; p < n*n; p++) { // n * n = número de vezes que o somatório acontece na matriz
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [&turn]() { return (turn == 2); }); 
        
        int sum = 0;

        for(int l = 0; l < n; l++){
            
            sum += matrix1[i][l] * matrix2[l][j];
            
        }

        result = sum;

        turn = 1; 

        cv.notify_one(); 
    }
}


       

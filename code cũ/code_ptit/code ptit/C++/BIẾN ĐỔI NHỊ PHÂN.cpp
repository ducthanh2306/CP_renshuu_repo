#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        long long row, col;
        cin >> row >> col;
        long long A[row][col];
        for(int i = 0;i< row;i++){
            for(int j = 0; j< col;j++){
                cin >> A[i][j];
            }
        }
        long long B[row][col];
        for(int i = 0;i< row;i++){
            for(int j = 0; j< col;j++){
                B[i][j] = A[i][j]; 
            }
        }
        for(int i = 0;i< row;i++){
            for(int j = 0; j< col;j++){
                if( A[i][j] == 1){
                    for(int k = 0;k< row;k++){
                        B[k][j] = 1;
                    }
                    for(int z = 0;z< col;z++){
                        B[i][z] = 1;
                    }
                }
            }
        }
        for(int i = 0;i< row;i++){
            for(int j = 0; j< col;j++){
                cout << B[i][j] << " ";
            }
            cout << endl;
        }
    }
}


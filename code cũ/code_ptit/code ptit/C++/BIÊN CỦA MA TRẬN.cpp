#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        long long row;
        cin >> row ;
        long long col = row;
        vector<vector<int>> v(row,vector<int>(row));
        for(int i = 0;i< row;i++){
            for(int j = 0;j<row;j++){
                cin >> v[i][j];
            }
        }
        for(int i = 0;i< row;i++){
            if (i == 0 || i == row - 1){
                for(int k = 0;k< row;k++){
                    cout << v[i][k] << " ";
                }
                if (i == 0) cout << endl;
            } else{
                for (int z = 0; z < row;z++){
                    if( z == 0 || z == row - 1){
                        cout << v[i][z];
                        if (z == 0){
                            for(int u = 1; u<= (col-2) * 2 +1;u++){
                                cout << " ";
                            }
                        }
                    } 
                    if(z == row - 1) cout << "\n";
                }
            }
        }
        cout << endl;
    }
}


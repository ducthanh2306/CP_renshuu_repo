#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

int main(){
    int n,m, p;
    cin >> n >> m >> p;
    vector<vector<int>> v1(n,vector<int>(m));
    for(int i = 0;i< n;i++){
        for(int j = 0 ; j < m;j++){
            cin >> v1[i][j];
        }
    }
    vector<vector<int>> v2(m,vector<int>(p));
    for(int i = 0;i< m;i++){
        for(int j = 0 ; j < p;j++){
            cin >> v2[i][j];
        }
    }
    vector<vector<int>> v3(n,vector<int>(p));
    for(int i = 0;i < n;i++){
        for(int j = 0 ; j < p;j++ ){
            for(int k = 0; k < m ;k++){
                v3[i][j] += v1[i][k] * v2[k][j];
            }
        }
    }
    for(int i = 0;i< n;i++){
        for(int j = 0 ; j < p;j++){
            cout << v3[i][j] << " ";
        }
        cout << endl;
    }

}
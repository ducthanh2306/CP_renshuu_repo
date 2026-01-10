#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        long long n;
        cin >> n;
        vector<vector<int>> v(n,vector<int>(n));
        for(int i = 0;i< n;i++){
            if(i % 2 == 0){
            for(int j = 0;j< n;j++){
                cin >> v[i][j];
            }
        } else{
            for(int j = n - 1;j >=0;j--){
                cin >> v[i][j];
        }
    }
        }
        for(int i = 0;i< n;i++){
            for(int j = 0;j<n;j++){
                cout << v[i][j] << " ";
            }
            cout << endl;
        }
        }
}


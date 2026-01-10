#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    long long t;
    cin >> t;
    while(t--){
        long long n;
        cin >> n;
        vector<long long> v(n);
        for(int j = 0;j< n;j++){
            cin >> v[j];
        }
        for (int i = n - 1; i >= 0;i--){
            if(v.at(i) <= 0) v.erase(v.begin() + i);
        }
        sort(v.begin(), v.end());
        if (v.empty() || v[0] != 1){
            cout << 1 << endl;
            continue;
        } 
        int dapan = 0,length = v.size();
        for(int k = 0; k < length - 1;k++){
            if (v.at(k+ 1) - v.at(k) > 1) {
                 dapan = v.at(k) + 1;
                break;
            }
        }
        if (dapan == 0 ) cout << v.back() + 1 << endl;
        else cout << dapan << endl;
    }
}

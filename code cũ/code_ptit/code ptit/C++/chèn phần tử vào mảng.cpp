#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

int main(){
    long long n,k,moi;
    cin >> n >> k >> moi;
    vector<int> v(n+1,0);
    for(int i = 0;i <n;i++){
        cin >> v[i];
    }
    for(int i = n - 1;i >=k - 1;i--){
        v[i + 1] =v[i];
    }
    v[k - 1] = moi;
    for (int &x : v){
        cout << x << " ";
    }
}
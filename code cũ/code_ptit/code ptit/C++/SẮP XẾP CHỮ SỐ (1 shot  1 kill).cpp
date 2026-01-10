#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int main(){
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<string> v(n);
        for(string &s : v){
            cin >> s;
        }   
        string sum;
        for(string s : v){
            sum+= s;
        } 
        sort(sum.begin(),sum.end());
        vector< int> result;
        for(int i = 0 ; i < sum.size() - 1;i++){
            if (sum[i] != sum[i+ 1]){
                result.push_back(sum[i] - '0');
            }
        }
        result.push_back(sum[sum.size() - 1] - '0');
        sort(result.begin(),result.end());
        for(int k : result){
            cout << k << " ";
        } 
        cout << endl;
    }
}

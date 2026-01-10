#include <iostream>
#include <string>
#include <cctype> 
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    int t;
    cin >> t;
    cin.ignore();
    while(t--){
    string s;
    vector<char> v1; 
    getline(cin,s);
    string s1 = s;
    sort(s.begin(),s.end());
    for(int i = 0; i < s.size();i++){
        if ( i > 0 && s[i] != s[i-1] && s[i] != s[i+1] && i < s.size() - 1) {
            v1.push_back(s[i]);
        }
        if( i == 0 && s[i + 1] != s[i]) {
            v1.push_back(s[i]);
        }
        if ( i == s.size() - 1 && s[i - 1] != s[i]){
            v1.push_back(s[i]);
        }
    }
    for(size_t i =0;i< s1.size();i++){
        for(size_t j = 0 ;j< v1.size();j++){
            if(s1[i] == v1[j]) cout << s1[i];
        }
    }
    cout << endl;
    }
}

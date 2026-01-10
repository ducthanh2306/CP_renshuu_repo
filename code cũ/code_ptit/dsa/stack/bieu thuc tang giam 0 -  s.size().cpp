#include <bits/stdc++.h>
using namespace std;
string xuly(string s){
    string res;
    stack<int> st;
    for(int i = 0; i <= s.size();i++){
        st.push(i + 1);
        if(i == s.size() || s[i] == 'I'){
            while(!st.empty()){
                res += to_string(st.top());
                st.pop();
            }
        }
    }
    return res;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    long long t;
    cin >> t;
    while(t--){
        string s;
        cin >> s;
        cout << xuly(s) << "\n";
    }
}
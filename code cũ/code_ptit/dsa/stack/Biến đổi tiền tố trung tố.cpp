#include<bits/stdc++.h>
using namespace std;
bool isop(string c){
    return c == "+" || c == "-" ||c == "*" ||c == "/";
}
string trungto(string s){
    stack<string> st;
    for(int i = s.size() - 1; i >= 0;i--){
        string c = string(1,s[i]);
        if(isop(c)){
            string a = st.top();st.pop();
            string b = st.top();st.pop();
            if(c == "+"){
                st.push("(" + a + "+" + b + ")");
            }else if(c == "-")st.push("(" + a + "-" + b + ")");
            else if(c == "/")st.push("(" + a + "/" + b + ")");
            else if(c == "*")st.push("(" + a + "*" + b + ")");
        }else st.push(c);
    }
    return st.top();
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    cin.ignore();
    while(t--){
        string s;
        cin >> s;
        cout << trungto(s);
        cout << "\n";
    }
    
}
#include <bits/stdc++.h>
using namespace std;
vector<long long> dautiennhohonbenphai(vector<long long> a){
    stack<long long> st;
    vector<long long> v(a.size(),-1);
    for(long long i = a.size() - 1; i >= 0 ; i--){

        while(!st.empty() && a[st.top()] >= a[i]) {
            st.pop();
        }
        if(!st.empty()) v[i] = st.top();
        st.push(i);

    }
    return v;
}
vector<long long> dautiennhohonbentrai(vector<long long> a){
    stack<long long> st;
    vector<long long> v(a.size(),-1);
    for(long long i = 0; i < a.size() ; i++){

        while(!st.empty() && a[st.top()] >= a[i]) {
            st.pop();
        }
        if(!st.empty()) v[i] = st.top();
        st.push(i);

    }
    return v;
}


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    long long t;
    cin >> t;
    while(t--){
        long long n;
        cin >> n;
        long long res = 0;
       vector<long long> a(n);
       for(long long &x : a) cin >> x;
       vector<long long> left = dautiennhohonbentrai(a);
       vector<long long> right = dautiennhohonbenphai(a);

       for(long long i = 0; i < n;i++){
            long long l = (left[i] != -1 ? left[i]  + 1: 0);
            long long r = (right[i] != -1 ? right[i]  - 1: n - 1);
            long long area = a[i] *( r - l + 1);
            res = max(res,area);
       }
       cout << res << "\n";
    }
}
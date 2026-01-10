#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> adj;
vector<vector<int>> sscs;
vector<int> tin,low;
int timer = 0;
bool inStack[1001] = {false};
stack<int> st;
void dfs(int u){
    tin[u] = low[u] = ++timer;
    st.push(u);
    inStack[u] = true;
    for(int v : adj[u]){
        if(tin[v] == 0){
            dfs(v);
            low[u] = min(low[u],low[v]);
        }else if(inStack[v]){
            low[u] = min(low[u],tin[v]);
        }
    }

    if(tin[u] == low[u]){
        vector<int> ssc;
        while(true){
            int v = st.top();st.pop();
            inStack[v] = false;
            ssc.push_back(v);
            if(u == v) break;
        }
        sscs.push_back(ssc);
    }
}

int main(){
    int t;
    cin >> t;
    while(t--){
        int n,m;
        cin >> n >> m;
        adj.assign(n + 1,{});
        for(int i = 0 ; i < m;i++){
            int u,v;
            cin >> u  >> v;
            adj[u].push_back(v);
        }
        tin.assign(n + 1,0);
        low.assign(n+1,0);
        timer = 0;
        sscs.clear();
        st = stack<int>();
        memset(inStack,false,sizeof(inStack));
        for(int i = 1; i <= n;i++){
            if(tin[i] == 0) dfs(i);
        }
        if(sscs.size() == 1) cout << "YES";
        else cout << "NO";
        cout << endl;
    }
}

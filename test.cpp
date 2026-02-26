#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
int n,m;
int timer = 0;
vector<vector<int>> scc,adj;
int tin[MAXN],low[MAXN];
bool onStack[MAXN];
stack<int> st;
void dfs(int u ){
    low[u] = tin[u] = ++timer;
    st.push(u);
    onStack[u] = true;
    for(int v : adj[u]){
        if(tin[v] == 0){
            dfs(v);
            low[u] = min(low[u],low[v]);
        }else if(onStack[v]){
            low[u] = min(low[u],tin[v]);
        }
    }
    if(tin[u] == low[u]){
        vector<int> component;
        while(true){
            int tp = st.top();
            onStack[tp] = false;
            component.push_back(tp);            
            st.pop();
            if(tp == u){
                break;
            }
        }
        scc.push_back(component);
    }
}


int main() {
    cin >> n >> m;
    adj.resize(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);  // đồ thị có hướng
    }

    for (int i = 1; i <= n; i++) {
        if (tin[i] == 0)
            dfs(i);
    }

    cout << "So SCC: " << scc.size() << "\n";
    for (auto &comp : scc) {
        for (int x : comp)
            cout << x << " ";
        cout << "\n";
    }

    return 0;
}

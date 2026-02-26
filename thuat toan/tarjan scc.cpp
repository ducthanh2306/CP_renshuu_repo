#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

vector<int> adj[MAXN];
int n, m;

int timer = 0;
int tin[MAXN], low[MAXN];
bool onStack[MAXN];
stack<int> st;

vector<vector<int>> scc; // lưu các SCC

void dfs(int u) {
    tin[u] = low[u] = ++timer;
    st.push(u);
    onStack[u] = true;

    for (int v : adj[u]) {
        if (tin[v] == 0) {  // chưa thăm
            dfs(v);
            low[u] = min(low[u], low[v]); // min vi v ve duoc to tien cua no thi u cung ve duoc , va neu u < low[v] thi ko cap nhat (to tien xa hon)
        } 
        else if (onStack[v]) {  // back-edge
            low[u] = min(low[u], tin[v]);  // min vi co the tu 1 dinh co 2 canh ve to tien cua no
        }
    }

    // nếu u là root của SCC
    if (low[u] == tin[u]) {
        vector<int> component;
        while (true) {
            int v = st.top();
            st.pop();
            onStack[v] = false;
            component.push_back(v);
            if (v == u) break;
        }
        scc.push_back(component);
    }
}

int main() {
    cin >> n >> m;

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

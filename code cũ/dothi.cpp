#include <bits/stdc++.h>
using namespace std;

struct Graph {
    int n;                      // số đỉnh
    vector<vector<int>> adj;    // danh sách kề

    Graph(int n) : n(n), adj(n + 1) {}

    void addEdge(int u, int v, bool directed = false) {
        adj[u].push_back(v);
        if (!directed) adj[v].push_back(u);
    }

    // ================= BFS =================
    vector<int> BFS(int start) {
        vector<int> dist(n + 1, -1);
        queue<int> q;

        dist[start] = 0;
        q.push(start);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v : adj[u]) {
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }
        return dist;   // trả về khoảng cách từ start đến các đỉnh khác
    }

    // ================= DFS =================
    vector<int> visited;

    void dfsUtil(int u) {
        visited[u] = 1;
        // xử lý đỉnh u tại đây nếu muốn

        for (int v : adj[u]) {
            if (!visited[v]) dfsUtil(v);
        }
    }

    void DFS(int start) {
        visited.assign(n + 1, 0);
        dfsUtil(start);
    }

    // ================= Thành phần liên thông =================
    int countConnectedComponents() {
        visited.assign(n + 1, 0);
        int components = 0;

        for (int i = 1; i <= n; i++) {
            if (!visited[i]) {
                components++;
                dfsUtil(i);
            }
        }
        return components;
    }

    // ================= Tìm chu trình (cycle) trong đồ thị vô hướng =================
    bool hasCycleUndirected() {
        visited.assign(n + 1, 0);
        function<bool(int,int)> dfs = [&](int u, int parent) {
            visited[u] = 1;
            for (int v : adj[u]) {
                if (!visited[v]) {
                    if (dfs(v, u)) return true;
                } else if (v != parent) {
                    return true; // gặp đỉnh đã thăm và không phải cha → chu trình
                }
            }
            return false;
        };

        for (int i = 1; i <= n; i++)
            if (!visited[i])
                if (dfs(i, -1)) return true;

        return false;
    }

    // ================= Tìm chu trình trong đồ thị có hướng =================
    bool hasCycleDirected() {
        vector<int> state(n + 1, 0);
        // 0 = chưa thăm
        // 1 = đang thăm (trên stack)
        // 2 = đã xong

        function<bool(int)> dfs = [&](int u) {
            state[u] = 1;
            for (int v : adj[u]) {
                if (state[v] == 0) {
                    if (dfs(v)) return true;
                } else if (state[v] == 1) {
                    return true; // back-edge → chu trình
                }
            }
            state[u] = 2;
            return false;
        };

        for (int i = 1; i <= n; i++)
            if (state[i] == 0)
                if (dfs(i)) return true;

        return false;
    }

    // ================= Topo Sort (Kahn) =================
    vector<int> topoSort() {
        vector<int> indeg(n + 1, 0);
        for (int u = 1; u <= n; u++)
            for (int v : adj[u])
                indeg[v]++;

        queue<int> q;
        for (int i = 1; i <= n; i++)
            if (indeg[i] == 0)
                q.push(i);

        vector<int> order;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            order.push_back(u);

            for (int v : adj[u]) {
                indeg[v]--;
                if (indeg[v] == 0)
                    q.push(v);
            }
        }

        // Nếu số phần tử < n → có chu trình
        if ((int)order.size() < n)
            return {}; // trả về rỗng để báo lỗi

        return order;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    Graph g(n);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v, false);
    }

    // ví dụ test
    auto dist = g.BFS(1);
    auto topo = g.topoSort();
    bool cyc = g.hasCycleUndirected();

    return 0;
}
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;
vector<int> tin, low;
vector<bool> onStack;
stack<int> st;
int timer;
vector<vector<int>> SCCs;

void dfs(int u) {
    tin[u] = low[u] = ++timer;
    st.push(u);
    onStack[u] = true;

    for (int v : adj[u]) {
        if (tin[v] == 0) {                // v chưa thăm
            dfs(v);
            low[u] = min(low[u], low[v]);
        } 
        else if (onStack[v]) {            // v trong stack → có back-edge
            low[u] = min(low[u], tin[v]);
        }
    }

    // Nếu u là "gốc" của SCC
    if (low[u] == tin[u]) {
        vector<int> scc;
        while (true) {
            int v = st.top(); st.pop();
            onStack[v] = false;
            scc.push_back(v);

            if (v == u) break;
        }
        SCCs.push_back(scc);
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    adj.assign(n+1, {});
    tin.assign(n+1, 0);
    low.assign(n+1, 0);
    onStack.assign(n+1, false);
    timer = 0;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    for (int i = 1; i <= n; i++) {
        if (tin[i] == 0)
            dfs(i);
    }

    // In kết quả
    cout << "Number of SCCs: " << SCCs.size() << "\n";
    for (auto &comp : SCCs) {
        for (int x : comp) cout << x << " ";
        cout << "\n";
    }
}

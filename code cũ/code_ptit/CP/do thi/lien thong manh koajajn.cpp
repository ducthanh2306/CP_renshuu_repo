#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
vector<int> adj[MAXN];      // Đồ thị gốc
vector<int> rev_adj[MAXN];  // Đồ thị đảo chiều (Reversed Graph)
bool visited[MAXN];
stack<int> st;              // Stack lưu thứ tự duyệt xong

// Bước 1: DFS xuôi để điền vào Stack
void dfs1(int u) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs1(v);
        }
    }
    // Quan trọng: Duyệt xong u rồi mới đẩy vào stack
    st.push(u); 
}

// Bước 3: DFS ngược để tìm SCC
void dfs2(int u, vector<int>& currentSCC) {
    visited[u] = true;
    currentSCC.push_back(u); // Thêm đỉnh vào nhóm hiện tại
    for (int v : rev_adj[u]) {
        if (!visited[v]) {
            dfs2(v, currentSCC);
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);       // Cạnh xuôi
        rev_adj[v].push_back(u);   // Cạnh ngược (Bước 2: Tạo đồ thị đảo ngay khi nhập)
    }

    // --- BƯỚC 1: Duyệt DFS đầu tiên ---
    memset(visited, false, sizeof(visited));
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfs1(i);
        }
    }

    // --- BƯỚC 3: Xử lý Stack và tìm SCC ---
    memset(visited, false, sizeof(visited)); // Reset lại mảng visited
    int sccCount = 0;
    
    while (!st.empty()) {
        int u = st.top();
        st.pop();
        
        if (!visited[u]) {
            sccCount++;
            vector<int> currentSCC;
            dfs2(u, currentSCC);
            
            // In ra thành phần liên thông mạnh vừa tìm được
            cout << "SCC " << sccCount << ": ";
            for (int node : currentSCC) cout << node << " ";
            cout << endl;
        }
    }

    return 0;
}
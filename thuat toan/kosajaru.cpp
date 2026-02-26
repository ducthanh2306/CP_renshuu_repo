#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
int n,m;
vector<vector<int>> adj(1001),rev_adj(1001);
vector<vector<int>> scc;
;
stack<int> st;
bool visited[1005];
vector<int> tmp;
// kosajaru
void dfs1(int u) {
    visited[u] = true;
    for(int v : adj[u]){
        if(!visited[v]){
            dfs1(v);
        }
    }
    st.push(u);
}

void dfs2(int u){
    visited[u] = true;
    tmp.push_back(u);
    for(int v : rev_adj[u]){
        if(!visited[v]){
            dfs2(v);
        }
    }
}
void solve(){
    cin >> n;
    for(int i =1 ; i <=n;i++){
        for(int j = 1; j <=n;j++){
            int x;
            cin >> x;
            if(x){
                adj[i].push_back(j);
                rev_adj[j].push_back(i);
            } 
                
        }
    }
    for(int i = 1; i <=n;i++){
        if(!visited[i])dfs1(i);
    }
    memset(visited,false,sizeof(visited));
    while(!st.empty()){
        int cur = st.top();
        st.pop();
        if(!visited[cur]){
            dfs2(cur);
            scc.push_back(tmp);
            tmp.clear();
        }
    }
    if(scc.size() == 1) cout << "strongly connected";
    else cout << "not strongly connected";
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    solve();


    
}
// #include <bits/stdc++.h>
// using namespace std;

// int n;
// vector<vector<int>> adj(1005), rev_adj(1005);
// vector<vector<int>> scc;
// stack<int> st;
// bool visited[1005];
// vector<int> tmp;

// void dfs1(int u) {
//     visited[u] = true;
//     for(int v : adj[u]) {
//         if(!visited[v]) dfs1(v);
//     }
//     st.push(u);
// }

// void dfs2(int u) {
//     visited[u] = true;
//     tmp.push_back(u);
//     for(int v : rev_adj[u]) {
//         if(!visited[v]) dfs2(v);
//     }
// }

// void solve() {
//     if(!(cin >> n)) return;
    
//     // Reset dữ liệu để an toàn
//     for(int i = 1; i <= n; i++) {
//         adj[i].clear();
//         rev_adj[i].clear();
//         visited[i] = false;
//     }
//     scc.clear();

//     for(int i = 1; i <= n; i++) {
//         for(int j = 1; j <= n; j++) {
//             int x; cin >> x;
//             if(x) {
//                 adj[i].push_back(j);
//                 rev_adj[j].push_back(i);
//             }
//         }
//     }

//     // Pass 1: Fill stack
//     for(int i = 1; i <= n; i++) {
//         if(!visited[i]) dfs1(i);
//     }

//     // Pass 2: Duyệt đồ thị đảo theo thứ tự stack
//     memset(visited, false, sizeof(visited));
//     while(!st.empty()) {
//         int cur = st.top();
//         st.pop();
        
//         if(!visited[cur]) { // CỰC KỲ QUAN TRỌNG
//             tmp.clear();
//             dfs2(cur);
//             scc.push_back(tmp);
//         }
//     }

//     // Kiểm tra tính liên thông mạnh
//     // Lưu ý: Một đỉnh đơn lẻ không có cạnh tự nối vẫn là 1 SCC.
//     if(scc.size() == 1 && n > 0) {
//         // Đảm bảo SCC duy nhất đó chứa toàn bộ các đỉnh
//         if(scc[0].size() == n) cout << "strongly connected";
//         else cout << "not strongly connected";
//     } else {
//         cout << "not strongly connected";
//     }
// }

// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     solve();
//     return 0;
// }
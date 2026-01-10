#include <bits/stdc++.h>
using namespace std;

int main(){
    int T;
    cin >> T;
    while(T--){
        int n, m;
        cin >> n >> m;
        int s, t;
        cin >> s >> t;

        vector<vector<int>> adj(n + 1);
        for(int i = 0; i < m; i++){
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            // adj[v].push_back(u); // nếu vô hướng
        }

        vector<int> path;
        vector<bool> visited(n + 1, false);

        queue<pair<int, vector<int>>> q;
        q.push({s, {s}});
        visited[s] = true;

        while(!q.empty()){
            auto cur = q.front(); q.pop();

            if(cur.first == t){
                path = cur.second;
                break;
            }

            for(int v : adj[cur.first]){
                if(!visited[v]){
                    visited[v] = true;
                    auto tmp = cur.second;
                    tmp.push_back(v);
                    q.push({v, tmp});
                }
            }
        }

        if(path.empty()) cout << -1;
        else for(int x : path) cout << x << " ";
        cout << '\n';
    }
}

#include <bits/stdc++.h>
using namespace std;
bool visited[1001] = {false};
int found = false;
vector<int> path;
void dfs(int u ,int t,vector<vector<int>> &adj){
    if(found) return;
    if(u == t) {
        for(int x : path) cout << x << " ";
        cout << "\n";
        found = true;
        return;
    }
    
    for(int v : adj[u]){
        if(!visited[v]){
            visited[v] = true;
            path.push_back(v);
            dfs(v,t,adj);
            path.pop_back();
            
        }
        
    }
    
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while(t--){
        int n,m;
        cin >> n >> m;
        int s,t;
        cin >> s >> t;
        
        vector<vector<int>> adj(n + 1);
        for(int i = 0; i < m;i++){
            int u,v;
            cin >> u >> v;
            adj[u].push_back(v);
        }
        path.push_back(s);
        visited[s] = true;
        dfs(s,t,adj);
        if(!found) cout << -1 <<"\n";
        memset(visited,false,sizeof(visited));
        found = false;
        path.clear();
    }
}
        #include<bits/stdc++.h>
        using namespace std;
        bool visited[1001];
        int parent[1001];
        vector<vector<int>> adj;
        
        vector<vector<int>> paths;

        void bfs(int s){
            queue<int> q;
            q.push(s);
            visited[s] = true;
            while(!q.empty()){
                int top = q.front();q.pop();
                for(int v : adj[top]){
                    if(!visited[v]){
                        visited[v] = true;
                        parent[v] = top;
                        q.push(v);
                    }
                }
            }
        }
        void reset(int s){
            memset(visited,false,sizeof(visited));
            memset(parent,0,sizeof(parent));
        }
        void in(int s,int t){
            vector<int> path;
            int cur = t; 
            while(cur != s){
                path.push_back(cur);
                cur = parent[cur];
            }
            path.push_back(s);
            reverse(path.begin(),path.end());
            for(int x: path) cout << x << " ";
            cout <<"\n";
        }
        int main(){
            ios_base::sync_with_stdio(false);
            cin.tie(0);
            int t;
            cin >> t;
            while(t--){
                int n,m , s ;
                cin >> n >> m >> s;
                adj.assign(n + 1,{});
                for(int i = 0 ; i < m;i++){
                    int u,v;
                    cin >> u >> v;
                    adj[u].push_back(v);
                    adj[v].push_back(u);
                }
                
                reset(s);
                bfs(s);
                for(int i = 1; i <=n;i++){
                    if(i == s) continue;
                    if(!visited[i]){
                        cout << "No path" << "\n";
                    }else{
                        in(s,i);
                    }
                }
            }
        }
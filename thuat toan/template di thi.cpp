#include<bits/stdc++.h>
using namespace std;
vector<int> adj[100005];
int parent[100005];
bool visited[100005];
int isprime[10001]; // memset true o trong ham 
void sang(int n){
    isprime[0] = false;
    isprime[1] = false;
    for(int i = 2; i <= sqrt(n;i++)){
        if(isprime[i]){
            for(int j = i *i; j <= n; j+=i){
                isprime[j] = false;
            }
        }
    }
}
struct DSU {
    vector<int> parent, sz;

    DSU(int n) {
        parent.resize(n + 1);
        sz.assign(n + 1, 1);
        for (int i = 1; i <= n; i++)
            parent[i] = i;
    }

    int find(int x) {
        if (x == parent[x]) return x;
        return parent[x] = find(parent[x]);
    }

    void unite(int a, int b) {
        a = find(a); b = find(b);
        if (a != b) {
            if (sz[a] < sz[b]) swap(a, b);
            parent[b] = a;
            sz[a] += sz[b];
        }
    }
};

void bfs(int s){
    queue<int> q;
    q.push(s);
    visited[s] = true;
    while(!q.empty()){
        int u = q.front();q .pop();
        for(int v : adj[u]){
            if(!visited[v]){
                visited[v] = true;
                parent[v] = u;
                q.push(v);
            }
        }
    }
}
void dfs(int u){
    visited[u] = true;
    for(int v: adj[u]){
        if(!visited[v]){
            parent[v] = u;
            dfs(v);
        }
    }
}

void in(int s,int t){
    if(!visited[t]) {
        cout << "-1";
        return;
    }
    vector<int> path;
    int cur = t;
    while(cur != 0){
        path.push_back(cur);
        if(cur == s) break; 
        cur = parent[cur];
    }
    reverse(path.begin(),path.end());
    for(int x : path) cout << x << " ";
}

//kiem tra chu trinh vo huong thi dung dsu
vector<int> color(1000 + 1);
void tomau(int u,bool & hascycle){ // kiem tra chu trinh co huong 
    if(hascycle) return;
    color[u] = 1;
    for(int v : adj[u]){
        if(color[v] == 0){
            tomau(v,hascycle);
        }else if(color[v] == 1) {
            hascycle = true;
            return;
        }
    }
    color[u] = 2;
}
// kiem tra chu trinh bang dfs
bool hascycle = false;

void dfs(int u, int parent_){
    visited[u] = true;
    for(int v : adj[u]){
        if(!visited[v]){
            parent[v] = u;
            dfs(v, u);
        }
        else if(v != parent_){
            hascycle = true;
        }
    }
}
// cay nhi phan
struct Node{
    int data;
    Node *left;
    Node *right;
    Node(int n){
        data = n;
        left = right = nullptr;
    }
};

// insert kiểu u v c
void insert(Node *root, int u, int v, char c){
    if(!root) return;
    if(root->data == u){
        if(c == 'R') root->right = new Node(v);
        else root->left = new Node(v);
    }else {
        insert(root->left,u,v,c);
        insert(root->right,u,v,c);
    }
}
// insert kiểu mảng:
void build(Node* &root, int i, vector<int>& a){ // dau tham chieu
    if(i >= a.size()) return;
    root = new Node(a[i]);
    build(root->left, 2*i + 1, a);
    build(root->right, 2*i + 2, a);
}

void bfs(Node *root){
    if(root == nullptr )return; // quan trong
    queue<Node*> q;
    q.push(root);
    while(!q.empty()){
        auto top = q.front(); q.pop();
        cout << top->data << " ";
        
        if(top->left)q.push(top->left);// quan trong
        if(top->right)q.push(top->right);// quan trong
    }
    return;
}

vector<vector<int>> paths; // in duong tu goc den node lá trái/phải
void duyet(Node*root,vector<int> &path, bool isleft){
    if(root == nullptr) return;
    path.push_back(root->data);
    if(root->left == nullptr && root->right == nullptr && isleft == true){
        paths.push_back(path);
    }
    duyet(root->left,path,true);
    duyet(root->right,path,false);
    
    path.pop_back();
}
//dem so la
int cnt = 0;
void duyet(Node*root){
    if(root== nullptr) return;
    if(root->left == nullptr && root->right == nullptr) cnt++;
     duyet(root->left);
     duyet(root->right);
} 
 //QUAN TRỌNG CÂY TÌM KIẾM NHỊ PHÂN

// 1. HÀM INSERT (QUAN TRỌNG NHẤT - HỌC THUỘC)
void insert(Node *&root, int x) {
    if (root == NULL) {
        root = new Node(x); // Tạo node mới khi tìm thấy chỗ trống
        return;
    }
    if (x < root->data) {
        insert(root->left, x);  // Nhỏ hơn -> rẽ Trái
    } else if (x > root->data) { // (Nếu đề cho phép node trùng nhau thì bỏ else này đi)
        insert(root->right, x); // Lớn hơn -> rẽ Phải
    }
}

// 2. Hàm Tìm kiếm (Search)
bool search(Node *root, int x) {
    if (root == NULL) return false;
    if (root->data == x) return true;
    
    if (x < root->data) return search(root->left, x);
    return search(root->right, x);
}

// 3. Hàm Duyệt (Inorder - Để test)
void inorder(Node *root) {
    if (root == NULL) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

void solve() {
    int n;
    cin >> n;
    Node *root = NULL; // Luôn khởi tạo là NULL
    
    for (int i = 0; i < n; i++) {
        int x; 
        cin >> x;
        insert(root, x); // Nhét từng số vào cây
    }

    // Đề hỏi gì thì làm cái đó, ví dụ in ra Inorder:
    inorder(root);
}



#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Sử dụng hằng số vô cực đủ lớn
const long long INF = 1e18;

// Cấu trúc để lưu thông tin cạnh: {đỉnh kề, trọng số}
struct Edge {
    int to;
    int weight;
};

// Cấu trúc để lưu trạng thái trong Priority Queue: {khoảng cách, đỉnh}
typedef pair<long long, int> PLI;

void dijkstra(int startNode, int n, const vector<vector<Edge>>& adj) {
    // dist[i] lưu khoảng cách ngắn nhất từ startNode đến i
    vector<long long> dist(n + 1, INF);
    dist[startNode] = 0;

    // Priority Queue (hàng đợi ưu tiên) để luôn lấy ra đỉnh có dist nhỏ nhất
    // Mặc định priority_queue là max-heap, dùng greater để biến thành min-heap
    priority_queue<PLI, vector<PLI>, greater<PLI>> pq;
    pq.push({0, startNode});

    while (!pq.empty()) {
        long long d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        // Nếu khoảng cách lấy ra lớn hơn khoảng cách hiện tại đã biết -> bỏ qua
        if (d > dist[u]) continue;

        // Duyệt các đỉnh kề v của u
        for (auto& edge : adj[u]) {
            int v = edge.to;
            int w = edge.weight;

            // Thao tác Relax (Thư giãn)
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    // In kết quả
    cout << "Khoang cach tu dinh " << startNode << ":" << endl;
    for (int i = 1; i <= n; i++) {
        if (dist[i] == INF) cout << i << ": INF" << endl;
        else cout << i << ": " << dist[i] << endl;
    }
}

int main() {
    int n, m, startNode;
    // n: số đỉnh, m: số cạnh
    cin >> n >> m;
    vector<vector<Edge>> adj(n + 1);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        // Nếu là đồ thị vô hướng, thêm dòng: adj[v].push_back({u, w});
    }

    cin >> startNode;
    dijkstra(startNode, n, adj);

    return 0;
}
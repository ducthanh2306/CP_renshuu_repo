//Nếu bạn có một con đường "Hạng Nhất" đến A ($\text{Best path}$), nó sẽ mở rộng ra để tạo thành ứng cử viên cho đường Hạng Nhất (hoặc Nhì) đến B.
//Nếu bạn có một con đường "Hạng Nhì" đến A ($\text{Second best}$), nó cũng sẽ mở rộng ra để tạo thành ứng cử viên cho đường Hạng Nhì (hoặc Ba, Tư...) đến B. 

//->Mọi trạng thái hợp lệ ($dist1, dist2, \dots, distK$) của đỉnh $u$ đều phải được đẩy vào PQ để có cơ hội mở rộng sang các đỉnh lân cận.

const long long INF = 2e18;
// Lưu ý: pair<int, ll> trong adj nghĩa là {đỉnh kề, trọng số}
vector<vector<pair<int, ll>>> adj; 

void dijkstra(int startNode, int n, int endNode) {
    // 1. Khởi tạo
    vector<ll> dist1(n + 1, INF), dist2(n + 1, INF);
    vector<int> parent1(n + 1, -1), parent2(n + 1, -1); // Parent nên là int, không cần ll

    dist1[startNode] = 0;
    // dist2[startNode] vẫn là INF, vì đường ngắn nhì không thể là 0 ngay lập tức được

    // 2. Priority Queue chuẩn: {khoảng cách, đỉnh}
    // Phải đồng nhất kiểu dữ liệu là pair<ll, int>
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    
    pq.push({0, startNode});

    while (!pq.empty()) {
        long long d = pq.top().first; // Khoảng cách hiện tại
        int u = pq.top().second;      // Đỉnh hiện tại
        pq.pop();

        // LAZY UPDATE: Nếu khoảng cách này tệ hơn cả kỷ lục nhì hiện tại thì bỏ qua
        // (Vì ta cần tìm top 2, cái nào lớn hơn top 2 là vứt)
        if (d > dist2[u]) continue;

        // Duyệt các đỉnh kề
        for (auto edge : adj[u]) {
            int v = edge.first;       // Đỉnh kề
            long long w = edge.second; // Trọng số cạnh (Weight)
            long long d_new = d + w;   // Khoảng cách mới

            // TRƯỜNG HỢP 1: Phá kỷ lục vàng (Ngắn nhất)
            if (dist1[v] > d_new) {
                // Đẩy người cũ xuống hạng nhì
                dist2[v] = dist1[v];
                parent2[v] = parent1[v];
                pq.push({dist2[v], v}); // Đẩy trạng thái nhì vào hàng đợi luôn

                // Cập nhật người mới lên hạng nhất
                dist1[v] = d_new;
                parent1[v] = u; // Cha của v là u
                pq.push({dist1[v], v});
            }
            // TRƯỜNG HỢP 2: Không phá kỷ lục vàng, nhưng phá kỷ lục bạc (Ngắn nhì)
            else if (dist1[v] < d_new && d_new < dist2[v]) {
                dist2[v] = d_new;
                parent2[v] = u; // Cha của v (trên đường ngắn nhì) là u
                pq.push({dist2[v], v});
            }
        }
    }
}
#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    // Chỉ cần mảng kích thước 7 để lưu trạng thái hiện tại
    vector<int> dp(7, INF);

    // 1. Khởi tạo Base Case cho phần tử đầu tiên a[1]
    for (int v = 1; v <= 6; v++) {
        dp[v] = (a[1] == v ? 0 : 1);
    }

    // 2. Chuyển trạng thái từ i = 2 đến n
    for (int i = 2; i <= n; i++) {
        vector<int> next_dp(7, INF);
        for (int v = 1; v <= 6; v++) { // Mặt muốn đặt tại vị trí i
            int cost = (a[i] == v ? 0 : 1);
            
            for (int u = 1; u <= 6; u++) { // Mặt tại vị trí i-1
                // Điều kiện kề: u != v và u + v != 7
                if (u != v && u + v != 7) {
                    if (dp[u] != INF) {
                        next_dp[v] = min(next_dp[v], dp[u] + cost);
                    }
                }
            }
        }
        dp = next_dp; // Cuốn chiếu: hàng mới trở thành hàng cũ cho bước sau
    }

    // 3. Tìm kết quả nhỏ nhất trong các mặt có thể kết thúc ở n
    int ans = INF;
    for (int v = 1; v <= 6; v++) {
        ans = min(ans, dp[v]);
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
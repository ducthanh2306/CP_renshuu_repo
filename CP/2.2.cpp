#include <bits/stdc++.h>
using namespace std;
// cong thuc (gap + 2 )/ 3
void solve() {
    int n;
    string s;
    cin >> n >> s;

    // Lưu tất cả vị trí có số 1 (0-indexed)
    vector<int> ones;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') ones.push_back(i);
    }

    // Trường hợp đặc biệt: Không có số 1 nào
    if (ones.empty()) {
        cout << (n + 2) / 3 << "\n";
        return;
    }

    long long added = 0;

    // 1. Xử lý đoạn trống ở đầu (Prefix)
    int first_gap = ones[0]; // Số lượng số 0 trước số 1 đầu tiên
    if (first_gap >= 2) {
        added += (first_gap - 1 + 2) / 3 - 0; // Công thức tinh gọn: ceil((L-1)/3)
        // Lưu ý: (L-1+2)/3 tương đương ceil((L-1)/3.0)
    }
    // Thực tế: Đơn giản hơn là added += max(0, (ones[0] - 1 + 2) / 3);

    // 2. Xử lý các đoạn trống ở giữa
    for (int i = 0; i < (int)ones.size() - 1; i++) {
        int gap = ones[i+1] - ones[i] - 1;
        if (gap >= 3) {
            added += (gap - 2 + 2) / 3; // ceil((gap-2)/3)
        }
    }

    // 3. Xử lý đoạn trống ở cuối (Suffix)
    int last_gap = n - 1 - ones.back();
    if (last_gap >= 2) {
        added += (last_gap - 1 + 2) / 3; // ceil((L-1)/3)
    }

    cout << ones.size() + added << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}
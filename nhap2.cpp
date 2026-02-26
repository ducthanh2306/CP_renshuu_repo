#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Sử dụng long long cho kết quả đếm để tránh tràn số (dù bài này int có thể đủ nhưng long long an toàn hơn)
using ll = long long;

void solve() {
    int n;
    cin >> n;
    
    // Đọc mảng a, sử dụng 1-based index cho thuận tiện với đề bài
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    // Ngưỡng chia căn bậc hai
    // Với N = 2*10^5, sqrt(N) ~ 447. Chọn S = 450 là hợp lý.
    const int S = 450; 
    
    ll ans = 0;

    // PHẦN 1: Xử lý các a[i] > S
    // Ta duyệt i, nếu a[i] lớn, ta nhảy cóc để tìm j
    for (int i = 1; i <= n; ++i) {
        if (a[i] > S) {
            // j - i = a[i] * k  => j = i + a[i] * k
            // k là giá trị kỳ vọng của a[j]
            // Vòng lặp này chạy tối đa n/S lần
            for (ll k = 1; ; ++k) {
                ll j = i + (ll)a[i] * k;
                if (j > n) break;
                
                // Kiểm tra điều kiện: a[i] * a[j] == j - i
                // Tương đương: a[i] * a[j] == a[i] * k => a[j] == k
                if (a[j] == k) {
                    ans++;
                }
            }
        }
    }

    // PHẦN 2: Xử lý các a[i] <= S
    // Thay vì duyệt i, ta duyệt giá trị v từ 1 đến S (giả sử a[i] = v)
    for (int v = 1; v <= S; ++v) {
        // Với một giá trị v cố định, ta duyệt tất cả các j
        // Phương trình: v * a[j] = j - i  =>  i = j - v * a[j]
        for (int j = 1; j <= n; ++j) {
            ll dist = (ll)v * a[j];
            ll i = j - dist;
            
            // Kiểm tra i có hợp lệ không
            if (i >= 1) {
                // Kiểm tra xem tại vị trí i đó có đúng là giá trị v không
                if (a[i] == v) {
                    ans++;
                }
            }
        }
    }

    cout << ans << "\n";
}

int main() {
    // Tối ưu I/O để chạy nhanh hơn
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
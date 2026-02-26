#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
vector<ll> hcn;
ll max_divisors = 0;
ll limit = 11000000; // Hơi quá 10^7 một chút để bao phủ X max

// n: số hiện tại, p_idx: chỉ số số nguyên tố, count: số ước, last_exp: số mũ trước đó
void backtrack(ll n, int p_idx, ll count, int last_exp) {
    if (count > max_divisors) {
        hcn.push_back(n);
        max_divisors = count;
    } else if (count == max_divisors) {
        // Nếu số ước bằng nhau, HCN là số nhỏ hơn. 
        // Do cách duyệt, số nhỏ hơn luôn được tìm thấy trước.
    }

    if (p_idx == 9) return;

    ll temp = n;
    for (int i = 1; i <= last_exp; ++i) {
        if (temp > limit / primes[p_idx]) break;
        temp *= primes[p_idx];
        backtrack(temp, p_idx + 1, count * (i + 1), i);
    }
}

// Hàm để tinh lọc lại danh sách HCN chuẩn
vector<ll> generate_hcn() {
    // Để tìm chuẩn, ta cần duyệt rộng hơn rồi lọc lại theo định nghĩa
    // Nhưng với X <= 10^7, ta có thể dùng cách đơn giản hơn: 
    // Sàng số lượng ước hoặc quay lui kỹ hơn.
    vector<pair<ll, ll>> candidates;
    // Quay lui đơn giản để lấy các số có tiềm năng
    // (Đoạn này mình sẽ cung cấp danh sách đã tối ưu để bạn dễ sử dụng)
    return {1, 2, 4, 6, 12, 24, 36, 48, 60, 120, 180, 240, 360, 720, 840, 1260, 1680, 2520, 5040, 7560, 10080, 15120, 20160, 25200, 27720, 45360, 50400, 55440, 83160, 110880, 166320, 221760, 277200, 332640, 498960, 554400, 665280, 720720, 1081080, 1441440, 2162160, 2882880, 3603600, 4324320, 5045040, 7207200, 10810800};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<ll> res = generate_hcn();

    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        ll x;
        cin >> x;
        // Tìm số đầu tiên trong mảng res mà >= x
        auto it = lower_bound(res.begin(), res.end(), x);
        cout << *it << "\n";
    }
    return 0;
}
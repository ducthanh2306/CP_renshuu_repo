#include <iostream>
#include <vector>
#include <cmath>
#include <map>
using namespace std;

map<int, int> uocCache; // lưu số ước đã tính để không tính lại

int getUoc(int n) {
    if (uocCache.count(n)) return uocCache[n];

    int cnt = 0;
    for (int i = 1; i <= sqrt(n); ++i) {
        if (n % i == 0) {
            cnt++;
            if (n / i != i) cnt++;
        }
    }
    return uocCache[n] = cnt; // lưu kết quả để dùng lại
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<int> v(n + 1);
    vector<int> pre(n + 1, 0); // prefix sum số ước

    for (int i = 1; i <= n; ++i) {
        cin >> v[i];
        pre[i] = pre[i - 1] + getUoc(v[i]); // tính số ước có cache
    }

    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << pre[r] - pre[l - 1] << '\n';
    }

    return 0;
}

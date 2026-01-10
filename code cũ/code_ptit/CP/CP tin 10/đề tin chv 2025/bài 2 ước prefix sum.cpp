#include <iostream>
#include <vector>
using namespace std;

const int MAX = 1e6 + 1;
vector<int> uoc(MAX, 0); // số ước của mỗi số

// Bước 1: Tiền xử lý số ước
void preprocess() {
    for (int i = 1; i < MAX; ++i)
        for (int j = i; j < MAX; j += i)
            uoc[j]++;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    preprocess();

    int n, q;
    cin >> n >> q;
    vector<int> v(n + 1);
    vector<int> pre(n + 1, 0); // prefix sum số ước

    for (int i = 1; i <= n; ++i) {
        cin >> v[i];
        pre[i] = pre[i - 1] + uoc[v[i]];
    }

    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << pre[r] - pre[l - 1] << '\n';
    }

    return 0;
}

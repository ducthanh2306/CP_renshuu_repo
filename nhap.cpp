#include <bits/stdc++.h>
using namespace std;

void solve() {
    string s;
    if (!(cin >> s)) return;

    long long current_sum = 0;
    for (char c : s) current_sum += (c - '0');

    if (current_sum <= 9) {
        cout << 0 << "\n";
        return;
    }

    // Cần giảm đi ít nhất bao nhiêu để tổng <= 9
    long long target_reduction = current_sum - 9;
    vector<int> possible_reductions;

    for (int i = 0; i < s.length(); i++) {
        int digit = s[i] - '0';
        if (i == 0) {
            // Chữ số đầu tiên chỉ giảm về tối thiểu là 1
            if (digit > 1) possible_reductions.push_back(digit - 1);
        } else {
            // Các chữ số khác có thể giảm về 0
            if (digit > 0) possible_reductions.push_back(digit);
        }
    }

    // Sắp xếp mức giảm từ lớn đến bé
    sort(possible_reductions.rbegin(), possible_reductions.rend());

    int ops = 0;
    long long reduced = 0;
    for (int r : possible_reductions) {
        reduced += r;
        ops++;
        if (reduced >= target_reduction) break;
    }

    cout << ops << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
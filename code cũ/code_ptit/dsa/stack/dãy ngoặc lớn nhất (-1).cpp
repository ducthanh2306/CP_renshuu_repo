#include <bits/stdc++.h>
using namespace std;

void solve() {
    string s;
    cin >> s;
    stack<int> st;
    st.push(-1); // Điểm mốc cơ sở
    int max_len = 0;

    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '(') {
            st.push(i);
        } else {
            st.pop();
            if (!st.empty()) {
                // Tính độ dài từ mốc gần nhất trong stack
                max_len = max(max_len, i - st.top());
            } else {
                // Nếu rỗng, dùng i làm mốc mới
                st.push(i);
            }
        }
    }
    cout << max_len << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}
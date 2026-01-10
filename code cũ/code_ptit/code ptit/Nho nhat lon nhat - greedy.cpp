#include <bits/stdc++.h>
using namespace std;
//bai lam AC
string getMin(int m, int s) {
    if (s == 0 && m > 1) return "";  // vô nghiệm
    string res = "";
    int rem = s;
    for (int i = 0; i < m; i++) {
        for (int d = (i == 0 ? 1 : 0); d <= 9; d++) {
            if (rem - d <= (m - i - 1) * 9) {
                res.push_back(char('0' + d));
                rem -= d;
                break;
            }
        }
    }
    return res;
}

string getMax(int m, int s) {
    string res = "";
    int rem = s;
    for (int i = 0; i < m; i++) {
        for (int d = 9; d >= 0; d--) {
            if (rem - d >= 0 && rem - d <= (m - i - 1) * 9) {
                res.push_back(char('0' + d));
                rem -= d;
                break;
            }
        }
    }
    return res;
}

int main() {
    int m, s;
    cin >> m >> s;
    // Kiểm tra vô nghiệm
    if ((s == 0 && m > 1) || s > 9 * m) {
        cout << "-1 -1\n";
        return 0;
    }
    // Trường hợp m=1 và s=0 thì getMin trả "0"
    string mn = (s == 0 && m == 1) ? "0" : getMin(m, s);
    string mx = getMax(m, s);
    cout << mn << " " << mx << "\n";
    return 0;
}

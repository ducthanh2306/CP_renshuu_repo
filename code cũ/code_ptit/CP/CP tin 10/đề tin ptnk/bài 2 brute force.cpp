#include <bits/stdc++.h>
using namespace std;

int n, Pmax, D_target;
vector<int> stations;
int minCharge = INT_MAX;

void dfs(int pos, int pin, int index, int chargeCount) {
    // N?u d?n dích
    if (D_target - pos <= pin) {
        minCharge = min(minCharge, chargeCount);
        return;
    }

    // Duy?t qua các tr?m còn l?i
    for (int i = index; i < stations.size(); ++i) {
        int dist = stations[i] - pos;
        if (dist <= pin) {
            // TH1: s?c t?i tr?m này
            dfs(stations[i], Pmax, i + 1, chargeCount + 1);
            // TH2: b? qua (không c?n vi?t vì b?n dã xét tr?m sau r?i)
        }
    }
}

int main() {
    cin >> n >> Pmax >> D_target;
    stations.resize(n);
    for (int i = 0; i < n; ++i) cin >> stations[i];
    sort(stations.begin(), stations.end());

    dfs(0, Pmax, 0, 0);

    if (minCharge == INT_MAX) cout << -1;
    else cout << minCharge;
}


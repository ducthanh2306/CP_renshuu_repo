#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n, Pmax, target;
    cin >> n >> Pmax >> target;

    vector<int> station(n);
    for (int i = 0; i < n; ++i) {
        cin >> station[i];  // Nhập các trạm
    }

    // Sắp xếp trạm tăng dần
    sort(station.begin(), station.end());

    // Bước 1: kiểm tra các khoảng cách có vượt quá pin không?
    if (station[0] > Pmax) {
        cout << -1; return 0;
    }

    for (int i = 1; i < n; ++i) {
        if (station[i] - station[i - 1] > Pmax) {
            cout << -1; return 0;
        }
    }

    if (target - station[n - 1] > Pmax) {
        cout << -1; return 0;
    }

    // Bước 2: duyệt từng trạm và đếm số lần sạc
    int charges = 0;               // số lần sạc
    int battery = Pmax;            // pin còn lại
    int previous = 0;              // vị trí trước đó

    for (int i = 0; i < n; ++i) {
        int distance = station[i] - previous;
        if (battery < distance) {
            // Không đủ → phải sạc tại previous
            charges++;
            battery = Pmax;
        }
        battery -= distance;
        previous = station[i];
    }

    // Sau khi duyệt hết các trạm → xem có đủ đến đích không
    if (battery < target - previous) {
        charges++;
    }

    cout << charges;
}

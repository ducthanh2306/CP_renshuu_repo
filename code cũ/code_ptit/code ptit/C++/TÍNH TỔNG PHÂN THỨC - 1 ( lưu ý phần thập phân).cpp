#include <iostream>
#include <iomanip>  // Thư viện định dạng số thập phân
using namespace std;
int main() {
        double tong = 0;
        int k;
        cin >> k;
        for(double j = 1;j <= k;j++){
            tong = tong + 1.0/j;
        }
        cout << fixed <<  setprecision(4) << tong << endl;
}

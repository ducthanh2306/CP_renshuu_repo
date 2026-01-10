#include <bits/stdc++.h>
using namespace std; // lưu ý lần sau phải thêm 1.0 khi tính double nếu ko bị cút ngay
int main() {
    int n;
    cin >> n;
    char dapan1[15] = {'A','B','B','A','D','C','C','A','B','D','C','C','A','B','D'};
    char dapan2[15] = {'A', 'C', 'C', 'A', 'B', 'C', 'D', 'D', 'B', 'B', 'C', 'D', 'D', 'B', 'B'};
    for(int i = 1; i<= n;i++){
        long long a;
        cin >> a;
        char b[15];
        double diem =0;
        if(a == 101 ){
            for(int j = 0;j< 15;j++){
                cin >> b[j];
            }
            for(int m = 0; m < 15;m++){
                if (b[m] == dapan1[m]) diem = diem + 10.00/15;
            }
        }
        if(a == 102 ){
            for(int k = 0;k< 15;k++){
                cin >> b[k];
            }
            for(int s = 0; s < 15;s++){
                if (b[s] == dapan2[s]) diem = diem + 10.00/15;
            }
        }
        cout << fixed << setprecision(2) << diem << endl;
    }
}
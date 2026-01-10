#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;  // Number of test cases
    while (T--) {
        int n;
        cin >> n;
        vector<int> v(n);
        for(int i = 0 ; i < v.size();i++){
            cin >> v[i];
        }
        sort(v.begin(),v.end());
        int count = 0;
        for(int i = 0 ; i < v.size() - 1;i++){
            if (v[i + 1] - v[i] > 1){
                count +=  v[i + 1] - v[i] - 1;
            }
        }
        cout << count << endl;
    }
    return 0;
}
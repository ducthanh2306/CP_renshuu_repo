#include <bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin >> t; // hoac ta co the dung unordered_ set ko phai sort, insert vo xong check neu a[i] co nam trong set do ko
    while(t--){
        int n;
        cin >> n;
        vector<int> a(n + 1);
        for(int i = 1 ;i <=n;i++){
            cin >> a[i];
        }
        int ok = 1;
        bool visited[200005];
        memset(visited, false, sizeof(visited));
        vector<int> tmp;
        for (int i = 1 ; i <= n;i++){
            if (!visited[i]){
                vector<int> hehe;
                int j = i;
                while(j <=n){
                    visited[j] = true;
                    tmp.push_back(a[j]);
                    hehe.push_back(j);
                    j *= 2;
 
                }
                sort(tmp.begin(),tmp.end());
                if(tmp != hehe) {
                    ok = 0;
                    break;
                }
                tmp.clear();
            }
        }
        
        if (ok) cout << "YES";
        else cout << "NO";
        cout << "\n";
    }
}
#include<bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define FORD(i,a,b) for(int i = (a) - 1; i >= (b);i--) // duyet lui tu a - 1 -> 0

int n,k;
vector<int> a;
int ok = 0;


void sinh(){
    int i = k;
    while(i >= 1 && a[i] == n - k + i) i--;
    if(i == 0) ok = 1;
    else{
        a[i]++;
        FOR(j, i + 1,k + 1)a[j] = a[j - 1] + 1;
    }
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--){
        cin >> n >> k;
        a.assign(k + 1,0);
        set<int> se;
        FOR(i,1,k + 1) {
            cin >> a[i];
            se.insert(a[i]);
        }

        sinh();

        if(ok) cout << k << "\n";
        else {
            int cnt =0;
            FOR(i,1,k + 1){
                if(se.find(a[i]) == se.end()){
                    cnt++;
                }
            }
            cout << cnt << "\n";
        }
        ok = 0;
    }



}

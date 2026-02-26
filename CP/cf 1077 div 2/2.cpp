#include<bits/stdc++.h>  //https://codeforces.com/contest/2188/problem/B
using namespace std;

string s;
int n;
int sum = 0;
int hehe[200001];

// chi kiem tra so 1 duoc tao ra
void thaotacbentrai(int idx){
    if(idx < 0) return;
    int index = idx;
    while(index >= 0 && s[index] == '0')index--;
    if(index == -1){
        int zeroNum = idx + 1;
        sum += hehe[zeroNum + 1];
    }else{
        int zeroNum = idx - index - 1;
        sum+= hehe[zeroNum + 1];
    }
}
void thaotacbenphai(int idx){
    if(idx >= n) return;
    int index = idx;
    while(index < n && s[index] == '0')index++;
    if(index == n){
        int zeroNum =  n - 1 - idx + 1;
        sum += hehe[zeroNum + 1];
    }else{
        int zeroNum = index - idx - 1;
        sum+= hehe[zeroNum + 1];
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    hehe[0] = 0;
    int cnt = -1;
    for(int i = 1; i <= 200000;i++){
        if(cnt % 3 == 0){
            hehe[i] = hehe[i - 1] + 1;
        }else hehe[i] = hehe[i - 1];
        cnt++;
    }
    int t;
    cin >> t;
    while(t--){
        cin >> n;
        cin >> s;
        int oneNum = 0;
        bool firstOne = true;
        for(int i = 0 ; i < s.size();i++){
            if(s[i] == '1'){
                oneNum++;
                if(firstOne)thaotacbentrai(i - 2);
                firstOne = false;
                thaotacbenphai(i + 2);
            }
        }
        if(oneNum == 0){
            cout << hehe[s.size() + 1] << "\n";
            continue;
        }
        sum += oneNum;
        cout << sum << "\n";
        sum = 0;
    }
}


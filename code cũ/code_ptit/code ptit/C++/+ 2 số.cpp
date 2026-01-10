#include <iostream>
#include <string>
#include <limits>
using namespace std;

void equalizeDigit(string &s1, string &s2) {
    if (s1.size() > s2.size()) {
        s2 = string(s1.size() - s2.size(),'0') + s2;
    } else {
        s1 = string(s2.size() - s1.size(),'0') + s1;
    }
}

int main() {
    int t;
    cin >> t;
    cin.ignore();
    while (t--) {
        string s1, s2;
        cin>> s1 >> s2;
        equalizeDigit(s1, s2);
        string res;
        int count =0,digit = 0;
        for(int i = s1.size() - 1; i >= 0;i--){
            count = s1[i] -'0' + s2[i] -'0'+ digit;
            if (count >= 10){
                res.insert(0,1,count -10 +'0'  );
                digit = 1;
            } else{
                res.insert(0,1,count  +'0' );
                digit = 0;
            }
        }
        
        if (digit == 1) res= '1' + res;
        cout << res;
        cout <<  endl;
    }
}


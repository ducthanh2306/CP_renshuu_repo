#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>
using namespace std;
int main(){
    int t;
    cin >> t;
    cin.ignore();
    while(t--){
      string s;
      getline(cin,s);
      if (s.size() == 1) {cout << s[0] << 1 << endl;
      continue;}
      if (s[0] == s[s.size() - 1]){
        cout << s[0] << s.size() << endl;
      continue;
      }
      int count = 0;
      for(int i = 0 ; i < s.size() - 1;i++){
        if (s[i] == s[i+ 1]) count++;
        if ( s[i] != s[i+ 1] ){
            cout << s[i];
            cout << count + 1;
            count = 0;
        }
        if (s[i + 1] == s[s.size() -1]) {
          cout << s[i + 1] << s.size() - i - 1 ;
          break; // truong hop cuoi:a)
      }
    }
    cout << endl;
  }
}
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
        int count =0 ;
        count+= s.size();
        string str;
        for(int i = 0; i< s.size();i++){
            for(int j = i + 1; j< s.size();j++){
                str = s.substr(i, j - i + 1);
                if(str[0] == str[str.size() - 1]) count ++ ;
                str = "";
            }
        }
        cout << count << endl;
        
    }
}
// bai toi uu vjp hon 
#include <iostream>
#include <string>
using namespace std;

int main() {
    int t;
    cin >> t;
    cin.ignore(); // bỏ dòng enter sau số t

    while (t--) {
        string s;
        getline(cin, s);
        int count = 0;

        for (int i = 0; i < s.size(); i++) {
            for (int j = i; j < s.size(); j++) {
                if (s[i] == s[j]) {
                    count++;
                }
            }
        }

        cout << count << endl;
    }
}

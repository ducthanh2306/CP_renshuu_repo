#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>
using namespace std;
string chuanhoahovadem(string &s){
    s[0] = toupper(s[0]); 
    for(int i = 1 ;i < s.size();i++){
        s[i] = tolower(s[i]);
    }
    return s;
}
string chuanhoaten(string &s){
    for(int i = 0 ;i < s.size();i++){
        s[i] = toupper(s[i]);
    }
    return s;
}
int main(){
    string s;
    getline(cin,s);
    stringstream ss(s);
    string word;
    vector<string> letsgo;
    while(ss>> word){
        letsgo.push_back(word);
    }
    letsgo[letsgo.size() - 1] = chuanhoaten(letsgo[letsgo.size() - 1]);
    for(int i = 0 ; i < letsgo.size() - 1;i++){
        letsgo[i] = chuanhoahovadem(letsgo[i]);
    }
    string result;
    for(int i = 0 ; i < letsgo.size() - 1;i++){
        result += letsgo[i];
        if (i < letsgo.size() - 2) result += ' '; 
    }
    result += ',';
    result += ' ';
     result += letsgo.at(letsgo.size() - 1);
     cout << result;
}
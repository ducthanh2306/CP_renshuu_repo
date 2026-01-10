#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;
string tolower(string &s){
    for(char &c : s){
        c = tolower(c);
    }
    return s;
}
string firstRemain(string &s){
    s = s[0];
    return s;
}
int main(){
    string s;
    getline(cin,s);
    stringstream ss(s);
    vector<string> s1;
    string word;
    while(ss >> word){
        s1.push_back(word);
    }
    for(string &s : s1){
        s = tolower(s);
    }
    string result;
    result += s1[s1.size() - 1];
    for(int i = 0 ; i < s1.size() - 1;i++){
        s1[i] = firstRemain(s1[i]);
        result +=s1[i];
    }
    result += "@ptit.edu.vn";
    cout << result ;
    
}
#include <iostream>
#include <string>
#include <sstream>
// thuat toan skip loop
using namespace std;

int main(){
	string s = "28tech 28tech com vn blog AI    python";
	int cnt = 0;
	for(int i = 0; i < s.size(); i++){
		if(s[i] != ' '){
			++cnt;
			//duyet not cac ki tu cua tu bat dau tu chi so i
			while(i < s.size() && s[i] != ' '){
				++i;
			}
			--i;
		}
	}
	cout << "So luong tu trong xau : " << cnt << endl;
}
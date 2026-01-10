#include<iostream>
#include<string>
#include <climits>
#include <algorithm>
using namespace std;

int main() {
    int test; 
    cin >> test; 
    while (test--) {
        long long n,k; 
        cin >> n >> k; 
        long long A[n]; 
        for (long long i = 0; i < n; i++) {
            cin >> A[i];  
        } 
        sort(A, A + n); 
		
		cout << A[k - 1] << endl;
    } 
}
//huy an
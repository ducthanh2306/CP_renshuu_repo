#include<iostream>
#include<string>
#include <climits>
#include <algorithm>
using namespace std;

int main() {
    int test; 
    cin >> test; 
    while (test--) {
        long long n; 
        cin >> n; 
        long long A[n]; 
        for (long long i = 0; i < n; i++) {
            cin >> A[i];  
        } 
        sort(A, A + n); 
		long long max = 1000000005;
		
        for(long long j = 0; j < n;j++){
			if ( j == n - 1 ) break;
			if (max > abs(A[j ] - A [j+ 1])) max = abs(A[j ] - A [j+ 1]);
		}
		cout << max << endl;
    } 
}
//huy an
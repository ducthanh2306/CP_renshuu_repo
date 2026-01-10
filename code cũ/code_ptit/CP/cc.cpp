// Bên trong hàm main xử lý test case
long long dp[105][105]; // Giả sử N, M <= 100
memset(dp, 0, sizeof(dp));

if(matran[0][0] == 1) dp[0][0] = 1;

for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
        if(matran[i][j] == 1) {
            if(i > 0) dp[i][j] += dp[i-1][j]; // Cộng số cách từ ô phía trên
            if(j > 0) dp[i][j] += dp[i][j-1]; // Cộng số cách từ ô bên trái
        } else {
            dp[i][j] = 0; // Nếu là vật cản thì không có đường qua đây
        }
    }
}
cout << dp[n-1][m-1] << endl;
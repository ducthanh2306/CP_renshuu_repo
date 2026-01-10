int socc(long long n){
    int r,k = 10;
    while(n !=0 ){
         r = n % 10;
         if(r > k ) return 0;
         k = r;
        n /= 10;
    }
    return 1;
}
int main(){
    long long a,n;
    scanf("%lld",&n);
    for(int i = 1;i<= n ; i++){
        scanf("%lld",&a);
    if( socc(a) == 1){
        printf("YES\n");
    } else{
        printf("NO\n");
    }
}
}
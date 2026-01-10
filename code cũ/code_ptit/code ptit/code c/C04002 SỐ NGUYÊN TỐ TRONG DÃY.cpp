#include <stdio.h>
#include <math.h>

int snt(int n){
    if(n < 2) return 0;
    for(int i = 2;i <=sqrt(n);i++){
        if(n % i == 0) return 0;
    }
    return 1;
}
int main(){
    int n;
    scanf("%d",&n);
    for(int i = 1;i <= n;i++){
        int k;
        scanf("%d",&k);
        int s1[k];
        for(int j = 0;j < k;j++){
            scanf("%d",&s1[j]);
        }
        for(int z = 0; z < k;z++){
            if (snt(s1[z]) == 1) printf("%d ",s1[z]);
        }
        printf("\n");
    }
}
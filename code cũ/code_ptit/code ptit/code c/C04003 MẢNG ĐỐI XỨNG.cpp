#include <stdio.h>
#include <math.h>

int main(){
    int n;
    scanf("%d",&n);
    for(int i = 1;i <= n;i++){
        int k,dem =0;
        scanf("%d",&k);
        int s1[k];
        for(int j = 0;j < k;j++){
            scanf("%d",&s1[j]);
        }
        for(int z = 0; z < k/2;z++){
            if (s1[z] !=s1[k-z-1]) dem++;
        }
        if(dem == 0) {
            printf("YES\n");
        } else{
            printf("NO\n");
        }
    }
}
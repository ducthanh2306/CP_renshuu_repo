#include <stdio.h>

int main(){
    int n;
    scanf("%d",&n);
    for(int i = 1;i <= n;i++){
        int k;
        scanf("%d",&k);
        int s1[k];
        for(int j = 0;j< k;j++){
            scanf("%d",&s1[j]);
        }
        for(int z = 0;z< k;z++){
            if(s1[z] % 2 == 0) printf("%d ",s1[z]);
        }
        printf("\n");
    }
}
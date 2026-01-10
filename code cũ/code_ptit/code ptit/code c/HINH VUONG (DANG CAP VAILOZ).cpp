#include <stdio.h>
#include <math.h>
int main() {
    int n;
    scanf("%d",&n);
    for(int i = 1;i<=n;i++){
        int a,b,c,d;
        scanf("%d%d%d%d",&a,&b,&c,&d);
        if(a < c) {
        int e[2];
        e[0] = c;
        e[1] = b;
        int dodai1 = sqrt((e[0]-a) *(e[0]-a) + (e[1]-b) *(e[1]-b) );
        int dodai2 = sqrt((e[0]-c) *(e[0]-c) + (e[1]-d) *(e[1]-d) );
        if ( dodai1 == dodai2) printf("YES\n");
        else printf("NO\n");
        }
        if(a > c) {
            int e[2];
            e[0] = a;
            e[1] = d;
            int dodai1 = sqrt((e[0]-a) *(e[0]-a) + (e[1]-b) *(e[1]-b) );
            int dodai2 = sqrt((e[0]-c) *(e[0]-c) + (e[1]-d) *(e[1]-d) );
            if ( dodai1 == dodai2) printf("YES\n");
            else printf("NO\n");
            }
    }
}

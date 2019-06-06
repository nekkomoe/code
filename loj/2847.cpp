#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 3e5 + 10;
int n, a[N];
int mn[N], mx[N];
int tmn, tmx;
int nxtmn[N], nxtmx[N];
int ans;

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[i]);
    }
    for(int i = n ; i ; -- i) {
        while(tmn && a[i] <= a[mn[tmn]]) -- tmn;
        nxtmn[i] = tmn ? mn[tmn] : n + 1;
        mn[++ tmn] = i;
        while(tmx && a[i] > a[mx[tmx]]) -- tmx;
        nxtmx[i] = tmx ? mx[tmx] : n + 1;
        mx[++ tmx] = i;
    }
    for(int i = 1 ; i <= n ; ) {
        int j = i; while(nxtmn[i] > nxtmx[j]) j = nxtmx[j];
        i = j + 1;
        ++ ans;
    }
    printf("%d\n", ans);
}

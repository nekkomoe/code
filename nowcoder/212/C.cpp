#include <bits/stdc++.h>
using namespace std; typedef long long ll;
const int N = 1e5 + 10;
int n, m;
 
struct LN {
    int l, r, c;
} ln[N], a[N];
 
bool operator < (LN a, LN b) {
    return a.l == b.l ? a.r < b.r : a.l < b.l;
}
 
ll ans = -1;
 
ll f[N][1 << 7];
 
int tr[10], rev[10], nxt[N], vis[10];
 
void sol(int U) {
//  cout << bitset<6>(U) << endl;
    memset(vis, 0, sizeof vis);
    int tot = 0;
    for(int i = 1 ; i <= 7 ; ++ i) {
        if((U >> (i - 1)) & 1) {
            rev[i] = tot ++;
        }
    }
    int n = 0;
    for(int i = 1 ; i <= :: n ; ++ i) {
        if((U >> (ln[i].c - 1)) & 1) {
            a[++ n] = ln[i];
            vis[rev[ln[i].c]] = 1;
//          printf("push: %d\n", ln[i].c);
        }
    }
    for(int i = 0 ; i < m ; ++ i) if(!vis[i]) return ;
     
//  puts("fafa");
     
    for(int i = 1 ; i <= n ; ++ i) {
        int l = i + 1, r = n, k = -1;
        while(l <= r) {
            int mid = (l + r) >> 1;
            if(a[mid].l > a[i].r) k = mid, r = mid - 1;
            else l = mid + 1;
        }
        nxt[i] = k;
    }
     
//  for(int i = 1 ; i <= n ; ++ i) {
//      printf("nxt[%d] = %d\n", i, nxt[i]);
//  } puts("");
     
//  memset(f, -1, sizeof f);
    for(int i = 1 ; i <= n + 1 ; ++ i)
        for(int s = 0 ; s < (1 << m) ; ++ s)
            f[i][s] = -1;
    f[n + 1][0] = 0;
    for(int i = n ; i ; -- i) {
        int c = rev[a[i].c];
//      printf("c = %d\n", c);
        for(int s = 0 ; s < (1 << m) ; ++ s) {
            f[i][s] = max(f[i][s], f[i + 1][s]);
            if(nxt[i] != -1 && f[nxt[i]][s] != -1)
                f[i][s | (1 << c)] = max(f[i][s | (1 << c)], f[nxt[i]][s] + (ll) a[i].r - a[i].l);
        }
        f[i][1 << c] = max(f[i][1 << c], (ll) a[i].r - a[i].l);
//      for(int s = 0 ; s < (1 << m) ; ++ s) {
//          cout << "f[" << i << "][" << bitset<7>(s) << "] = " << f[i][s] << endl;
//      }
    }
//  cout << f[1][(1 << m) - 1] << endl;
    ans = max(ans, f[1][(1 << m) - 1]);
}
 
int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) scanf("%d%d%d", &ln[i].l, &ln[i].r, &ln[i].c);
    sort(ln + 1, ln + 1 + n);
    for(int s = 0 ; s < (1 << 7) ; ++ s) {
        int tot = 0;
        for(int i = 0 ; i < 7 ; ++ i) if((s >> i) & 1) ++ tot;
        if(tot == m) sol(s);
    }
    printf("%lld\n", ans);
}

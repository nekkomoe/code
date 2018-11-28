typedef long long ll;
#include <bits/stdc++.h>
using namespace std;
 
const int N=2e6 + 10;

struct FastIO {
    static const int S = 1e7;
    int wpos;
    char wbuf[S];
    FastIO() : wpos(0) {}
    inline int xchar() {
        static char buf[S];
        static int len = 0, pos = 0;
        if (pos == len)
            pos = 0, len = fread(buf, 1, S, stdin);
//        if (pos == len) exit(0);
        return buf[pos++];
    }
    inline int operator () () {
        int c = xchar(), x = 0;
        while (c <= 32) c = xchar();
        for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
        return x;
    }
    inline ll operator ! () {
        int c = xchar(); ll x = 0;
        while (c <= 32) c = xchar();
        for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
        return x;
    }
    inline void wchar(int x) {
        if (wpos == S) fwrite(wbuf, 1, S, stdout), wpos = 0;
        wbuf[wpos++] = x;
    }
    inline void operator () (ll x) {
        if (x < 0) wchar('-'), x = -x;
        char s[24];
        int n = 0;
        while (x || !n) s[n++] = '0' + x % 10, x /= 10;
        while (n--) wchar(s[n]);
        wchar('\n');
    }
    inline void space(ll x) {
        if (x < 0) wchar('-'), x = -x;
        char s[24];
        int n = 0;
        while (x || !n) s[n++] = '0' + x % 10, x /= 10;
        while (n--) wchar(s[n]);
        wchar(' ');
    }
    inline void nextline() {
        wchar('\n');
    }
    ~FastIO()
    {
        if (wpos) fwrite(wbuf, 1, wpos, stdout), wpos = 0;
    }
} io;


int n,c,m,a[N],lst[N],pre[N],tot=1;
void add(int i,int c){for(;i;i-=i&-i)a[i]+=c;}
void ask(int i,int &c){for(c=0;i<=n;i+=i&-i)c+=a[i];}
struct ASD{
    int l,r,ans,id;
    bool operator < (ASD b) const{return r<b.r||(r==b.r&&l<b.l);}
}rd[N];
bool cmp(ASD a,ASD b){return a.id<b.id;}
int main(){
    n = io(), c = io(), m = io(); 
    for(int i=1,t;i<=n;i++)t = io(),pre[i]=lst[t],lst[t]=i;
    for(int i=1;i<=m;i++)rd[i].l = io(), rd[i].r = io(),rd[i].id=i;
    sort(rd+1,rd+1+m);
    for(int i=1;i<=n;i++){
        add(pre[pre[i]],-1),add(pre[i],1);
        while(rd[tot].r==i)ask(rd[tot].l,rd[tot].ans),tot++;
    }
    sort(rd+1,rd+1+m,cmp);
    for(int i=1;i<=m;i++)io(rd[i].ans);
}

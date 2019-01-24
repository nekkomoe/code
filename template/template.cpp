#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	
}

/////////////////////////////////////////////////////////////////////////////////////////////

#include<cctype>
#define P(a) while(a isdigit(c=getchar()))
void U(int &x) {int c;P(!);x=c-48;P()x=x*10+c-48;}

/////////////////////////////////////////////////////////////////////////////////////////////

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
        if (pos == len) exit(0);
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

namespace defs
{
    // #define getc() (S == T && (T = (S = B) + fread(B, 1, 1 << 15, stdin), S == T) ? EOF : *S++)
    
    // char B[1 << 15], *S = B, *T = B;
    
#define getc() getchar()
    
    template <class Type> Type read()
    {
        Type aa;
        int bb = 1, ch;
        while (ch = getc(), (ch < '0' || ch > '9') && ch != '-');
        ch == '-' ? aa = 0, bb = -1 : aa = ch - '0';
        while (ch = getc(), ch >= '0' && ch <= '9') aa = aa * 10 + ch - '0';
        return bb == 1 ? aa : -aa;
    }
    
    const unsigned int rand_x = 1401010315;
    const unsigned int rand_y = 1000000019;
    
    unsigned int rand_cur;
    
    unsigned int rand_int()
    {
        return rand_cur = rand_cur * rand_x + rand_y;
    }
    
    const int inf = 1071026353;
    const int mod = 1000000007;
    const int modx = 998244353;
}

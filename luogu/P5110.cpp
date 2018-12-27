// luogu-judger-enable-o2
#include <bits/stdc++.h>
using namespace std;
//typedef long long ll;

const int mod = 1e9 + 7;

struct Mat {
    unsigned long long a[2][2];
    Mat() { memset(a, 0, sizeof a); }
    unsigned long long *operator [] (int x) { return a[x]; }
    Mat operator * (Mat t) {
        Mat r;
        const unsigned long long &a = this -> a[0][0];
        const unsigned long long &b = this -> a[0][1];
        const unsigned long long &c = this -> a[1][0];
        const unsigned long long &d = this -> a[1][1];
        
        const unsigned long long &e = t[0][0];
        const unsigned long long &f = t[0][1];
        const unsigned long long &g = t[1][0];
        const unsigned long long &h = t[1][1];
        
        r[0][0] = (a * e % mod + b * g % mod) % mod;
        r[0][1] = (a * f % mod + b * h % mod) % mod;
        r[1][0] = (c * e % mod + d * g % mod) % mod;
        r[1][1] = (c * f % mod + d * h % mod) % mod;
        
        return r;
    }
};

Mat pw(Mat a, unsigned long long b) {
    Mat c;
    c[0][0] = c[1][1] = 1;
    for( ; b ; b >>= 1, a = a * a)
        if(b & 1)
            c = c * a;
    return c;
}

const int T = 65536 + 10, N = T + 10;

Mat base, a[N], b[N], meta, fafafa;

Mat go(unsigned long long n) {

//    return pw(base, n);

//    cout << "sol in: " << n << endl;
        
    if(n <= T) return a[n];
    else return a[n % T] * b[n / T];
}

namespace Mker {
    unsigned long long SA,SB,SC;
    void init(){scanf("%llu%llu%llu",&SA,&SB,&SC);}
    unsigned long long rand() {
        SA^=SA<<32,SA^=SA>>13,SA^=SA<<1;
        unsigned long long t=SA;
        SA=SB,SB=SC,SC^=t^SA;return SC;
    }
    unsigned long long output;
    const int PPP = mod - 1;
    void fafa() {
        unsigned long long n = rand();
        n %= PPP;
        unsigned long long ans = go(n)[0][1];
        output ^= ans;
    }
    
    void sol() {
        meta[0][0] = meta[1][1] = 1;
        
        fafafa[0][0] = 1;
        
        base[0][0] = 233, base[0][1] = 1;
        base[1][0] = 666, base[1][1] = 0;
        
        a[0] = meta;
        for(int i = 1 ; i <= T ; ++ i) {
            a[i] = a[i - 1] * base;
        }
        
        b[0] = meta;
        for(int i = 1 ; i <= T ; ++ i) {
            b[i] = b[i - 1] * a[T];
        }
        
        int T; scanf("%d", &T);
        init();
        while(T --) fafa();
        
        cout << output << endl;
    }
}

int main() {
    Mker :: sol();
}


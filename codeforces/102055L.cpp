#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int pr[]={2,3,5,7,11,23,43,79};
const int M=(1<<8)-1;

mt19937 RandEngine(chrono::steady_clock::now().time_since_epoch().count());
ll RandInt(ll L,ll R){return uniform_int_distribution<ll>(L,R)(RandEngine);}

ll Mx=0;

ll gcd(ll a,ll b)
{
    if(!a||!b) return a|b;
    #define ctz __builtin_ctzll
    int shift=ctz(a|b);
    b>>=shift;
    while(a)
    {
        a>>=ctz(a);
        if(a<b)
            swap(a,b);
        a-=b;
    }
    return b<<shift;
    #undef ctz
}

ull Mul(ull a,ull b,ull P)
{
    ull c=(ll)a*b-(ll)((ull)((long double)a*b/P))*P;
    return (c+P)%P;
}

ll ksm(ll a,ll b,ll P)
{
    ll ret=1;
    for(;b;b>>=1,a=Mul(a,a,P))
        if(b&1)
            ret=Mul(ret,a,P);
    return ret;
}

bool Miller_Rabin(ll n)
{
    if(n==2||n==3||n==5||n==7||n==11||n==23||n==43||n==79)
        return true;
    if(~n&1)
        return false;
    for(int p:pr)
    {
        ll t=n-1,c=0;
        while(~t&1)
            t>>=1,++c;
        ll pw=ksm(p,t,n);
        if(pw==1)
            continue;
        bool f=(pw==n-1);
        while(c)
        {
            pw=Mul(pw,pw,n);
            f|=(pw==n-1);
            --c;
            if(pw==1&&!f)
                return false;
        }
        if(pw!=1||!f)
            return false;
    }
    return true;
}



const int mod = 1e9 + 7;

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}

ll getinv(ll n) {
    return pw(n, mod - 2);
}

const int N = 7010;
int vis[N], pri[N], tot;
int a[N]; // x = a[x] + (x - a[x])
int isp[N];

void init(int n) {
    for(int i = 2 ; i <= n ; ++ i) {
        if(!vis[i]) {
            pri[++ tot] = i;
            isp[i] = 1;
            for(int j = i ; j <= n ; j += i) {
                vis[j] = 1;
            }
        }
    }
    for(int i = 2 ; i <= n ; ++ i) {
        for(int j = 2 ; j <= i ; ++ j) {
            if(i - j >= 2 && isp[j] && isp[i - j]) {
                a[i] = j;
                break;
            }
        }
    }
}

#define isitp Miller_Rabin

void runprog() {
    ll n; scanf("%lld", &n);
    if(n == 12) {
        puts("2 2 2 2 2 2");
    } else if(n == 14) {
        puts("2 2 2 2 3 3");
    } else if(n <= 11) {
        puts("IMPOSSIBLE");
    } else if(n & 1) {
        ll p = n / 3 - 1;
        while(p >= 2 && !isitp(p)) {
            -- p;
        }
        -- p;
        while(p >= 2 && !isitp(p)) {
            -- p;
        }
        ll res = n - 2 - p * 3;
        printf("%lld %lld %lld %d %d %d\n", p, p, p, 2, a[res], res - a[res]);
    } else {
        ll p = n / 4 - 1;
        while(p >= 2 && !isitp(p)) {
            -- p;
        }
        -- p;
        while(p >= 2 && !isitp(p)) {
            -- p;
        }
        ll res = n - p * 4;
        printf("%lld %lld %lld %lld %d %d\n", p, p, p, p, a[res], res - a[res]);
    }
}

int main() {
    init(N - 1);
    int t; scanf("%d", &t);
    while(t --) {
        static int T = 0;
        printf("Case %d: ", ++ T);
        runprog();
    }
}

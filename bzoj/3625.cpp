#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define RI register int
int read() {
    int q=0;char ch=' ';
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9') q=q*10+ch-'0',ch=getchar();
    return q;
}
const int mod=998244353,N=1 << 22,G=3;
int n,m;
int A[N],B[N],C[N],rev[N],c[N],tmp[N],len[N];
int ksm(int x,int y) {
    int re=1;
    for(;y;y>>=1,x=1LL*x*x%mod) if(y&1) re=1LL*re*x%mod;
    return re;
}
const int inv2=ksm(2,mod-2);
void NTT(int *a,int n,int x) {
    for(RI i=0;i<n;++i) if(rev[i]>i) swap(a[i],a[rev[i]]);
    for(RI i=1;i<n;i<<=1) {
        int gn=ksm(G,(mod-1)/(i<<1));
        for(RI j=0;j<n;j+=(i<<1)) {
            int t1,t2,g=1;
            for(RI k=0;k<i;++k,g=1LL*g*gn%mod) {
                t1=a[j+k],t2=1LL*g*a[j+i+k]%mod;
                a[j+k]=(t1+t2)%mod,a[j+i+k]=(t1-t2+mod)%mod;
            }
        }
    }
    if(x==1) return;
    reverse(a+1,a+n);int inv=ksm(n,mod-2);
    for(RI i=0;i<n;++i) a[i]=1LL*a[i]*inv%mod;
}
void getrev(int t)
    {for(RI i=0;i<t;++i) rev[i]=(rev[i>>1]>>1)|((i&1)<<(len[t]-1));}
void getinv(int *a,int *b,int n) {
    if(n==1) {b[0]=ksm(a[0],mod-2);return;}
    getinv(a,b,n>>1);
    int kn=n<<1;getrev(kn);
    for(RI i=0;i<n;++i) c[i]=a[i],c[n+i]=0;
    NTT(c,kn,1),NTT(b,kn,1);
    for(RI i=0;i<kn;++i) b[i]=1LL*b[i]*(2-1LL*c[i]*b[i]%mod+mod)%mod;
    NTT(b,kn,-1);
    for(RI i=n;i<kn;++i) b[i]=0;
}
void getsqrt(int *a,int *b,int n) {
    if(n==1) {b[0]=1;return;}
    getsqrt(a,b,n>>1);int kn=n<<1;
    for(RI i=0;i<n;++i) tmp[i]=0;
    getinv(b,tmp,n),getrev(kn);
    for(RI i=0;i<n;++i) c[i]=a[i],c[n+i]=0;
    NTT(c,kn,1),NTT(b,kn,1),NTT(tmp,kn,1);
    for(RI i=0;i<kn;++i) b[i]=1LL*(b[i]+1LL*c[i]*tmp[i]%mod)%mod*inv2%mod;
    NTT(b,kn,-1);
    for(RI i=n;i<kn;++i) b[i]=0;
}
int ans[N];

int main()
{
    scanf("%d%d", &n, &m);
    int kn=1;while(kn<=m) kn<<=1,len[kn]=len[kn>>1]+1;
    len[kn<<1]=len[kn]+1;
    
    A[0] = 1;
    for(int i = 1, x ; i <= n ; ++ i) {
        scanf("%d", &x);
        if(x <= m) {
            A[x] -= 4;
        }
    }
    
    getsqrt(A,B,kn),++ B[0];
    getinv(B, ans, kn); 
    for(int i = 1 ; i <= m ; ++ i) {
        printf("%lld\n", ((ll) ans[i] * 2 % mod+ mod) % mod);
    }
}


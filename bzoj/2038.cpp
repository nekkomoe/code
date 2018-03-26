#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <map>
#include <string>
#include <vector>
#include <stack>
#include <cmath>
#include <queue>
#include <cstdio>
#include <set>
using namespace std;
 
const int N=600000;
 
struct bk{
    int l,r,id,b;
    long long u,d;
    bool operator < (bk a)const{
        return b<a.b||(b==a.b&&r<a.r);
    }
}bs[N];
bool cmp(bk a,bk b){return a.id<b.id;}
int n,m,a[N],l=1,r,cnt[N];
long long now;
void add(int i){
    now+=2*(cnt[a[i]]++)+1;
}
void rem(int i){
    now+=-2*(cnt[a[i]]--)+1;
}
long long gcd(long long a,long long b){return b?gcd(b,a%b):a;}
int main(){
    scanf("%d%d",&n,&m);
    int len=sqrt(n);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    for(int i=1;i<=m;i++)scanf("%d%d",&bs[i].l,&bs[i].r),bs[i].id=i,bs[i].b=bs[i].l/len;
    sort(bs+1,bs+1+m);
    for(int i=1;i<=m;i++){
        if(r<bs[i].r){for(r++;r<bs[i].r;r++)add(r);add(r);}
        if(l>bs[i].l){for(l--;l>bs[i].l;l--)add(l);add(l);}
        if(r>bs[i].r){for(;r>bs[i].r;r--)rem(r);}
        if(l<bs[i].l){for(;l<bs[i].l;l++)rem(l);}
        if(l==r){bs[i].u=0,bs[i].d=1;continue;}
        bs[i].u=now-(r-l+1);
        bs[i].d=(long long)(r-l+1)*(r-l);
        long long g=gcd(bs[i].u,bs[i].d);
        bs[i].u/=g;
        bs[i].d/=g;
    }
    sort(bs+1,bs+1+m,cmp);
    for(int i=1;i<=m;i++)printf("%lld/%lld\n",bs[i].u,bs[i].d);
}

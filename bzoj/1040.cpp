#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <cmath>
#include <set>
#include <string>
 
using namespace std;
 
const int N=2000000;
 
int head[N],rest[N],to[N],tot=1;
long long f[N],g[N],ans;
void add(int from,int t){
    tot++;
    to[tot]=t;
    rest[tot]=head[from];
    head[from]=tot;
}
int n,a[N],v[N],U,V,E;
 
void dfs(int x,int f){
    v[x]=1;
    for(int i=head[x];i;i=rest[i]){
        if((i^1)==f)continue;
        if(v[to[i]]){
            U=x,V=to[i],E=i;
            continue;
        }
        dfs(to[i],i);
    }
}
 
void dp(int x,int fr,int line){
    f[x]=a[x];
    g[x]=0;
    for(int i=head[x];i;i=rest[i]){
        if(i==line||(i^1)==line||(i^1)==fr)continue;
        dp(to[i],i,line);
        f[x]+=g[to[i]];
        g[x]+=max(f[to[i]],g[to[i]]);
    }
}
 
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        int hate;
        scanf("%d%d",&a[i],&hate);
        add(i,hate);
        add(hate,i);
    }
    for(int i=1;i<=n;i++){
        if(!v[i]){
            dfs(i,0);
            dp(U,0,E);
            long long t=g[U];
            dp(V,0,E);
            ans+=max(g[V],t);
        }
    }
    printf("%lld\n",ans);
}


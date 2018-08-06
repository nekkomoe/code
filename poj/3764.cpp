#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
using namespace std;
 
const int N=200010;
int h[N],r[N],to[N],w[N],tot,n,k,root,ans,sz[N],f[N],dep[N],d[N],v[N],num,sum;
void insert(int u,int v,int z){
    to[tot]=v;
    r[tot]=h[u];
    w[tot]=z;
    h[u]=tot++;
}
void ins(int u,int v,int z){insert(u,v,z);insert(v,u,z);}
 
int ch[N * 35][2], ccc = 1;
 
void add(int x) {
    int rt = 1;
    for(int i = 30 ; ~ i ; -- i) {
        int bit = (x >> i) & 1;
        if(!rt[ch][bit]) {
            rt[ch][bit] = ++ ccc;
        }
        rt = rt[ch][bit];
    }
}
 
int query(int x) {
    int ret = 0;
    int rt = 1;
    for(int i = 30 ; ~ i ; -- i) {
        int bit = (x >> i) & 1;
        if(rt[ch][bit ^ 1]) {
            ret |= 1 << i;
            rt = rt[ch][bit ^ 1];
        } else {
            rt = rt[ch][bit];
        }
    }
    return ret;
}
 
void dfs(int u, int fa) {
    for(int i = h[u] ; ~i ; i = r[i]) {
        int v = to[i];
        if(v == fa) continue;
        dep[v] = dep[u] ^ w[i];
        add(dep[v]);
        ans = max(ans, query(dep[v]));
        dfs(v, u);
    }
}
 
int main(){
    while(scanf("%d",&n)==1){
        memset(h,-1,sizeof(h));
        memset(v,0,sizeof(v));
        memset(ch, 0, sizeof ch), ccc = 1;
        ans=0;
        root=0;
        tot=0;
        for(int i=1,u,v,z;i<n;i++){
            scanf("%d%d%d",&u,&v,&z);
            ins(u,v,z);
        }
        dfs(1, 0);
        dfs(1, 0);
        printf("%d\n",max(ans, query(0)));
    }
}

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <map>
#include <string>
#include <vector>
#include <stack>
using namespace std;
 
const int N=500000;
int head[N],rest[N],to[N],out[N],tot=1;
int h[N],r[N],t[N];
void add(int u,int v,int *to_=to,int *rest_=rest,int *head_=head){
    tot++;
    to_[tot]=v;
    rest_[tot]=head[u];
    head_[u]=tot;
}
 
bool v[N],inq[N];
int dfn[N],low[N],bel[N],cnt,scc;
stack<int>s;
void tarjan(int x){
    v[x]=inq[x]=1;
    dfn[x]=low[x]=++cnt;
    s.push(x);
    for(int i=head[x];i;i=rest[i]){
        if(!v[to[i]]){
            tarjan(to[i]);
            low[x]=min(low[x],low[to[i]]);
        }else if(inq[to[i]])low[x]=min(low[x],dfn[to[i]]);
    }
    if(low[x]==dfn[x]){
        scc++;
        int now=-1;
        while(now!=x){
            now=s.top();s.pop();
            inq[now]=0;
            bel[now]=scc;
            ++out[scc];
        }
    }
}
 
int n,m,ans;
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        add(u,v);
    }
    for(int i=1;i<=n;i++)if(!v[i])tarjan(i);
    cnt=0;
    for(int i=1;i<=n;i++)
        for(int j=head[i];j;j=rest[j])
            if(bel[i]!=bel[to[j]])
                add(bel[i],bel[to[j]],t,r,h);
    for(int i=1;i<=scc;i++){
        if(!h[i]){
            if(ans)exit(printf("0\n")&0);
            else ans=out[i];
        }
    }
    printf("%d\n",ans);
}

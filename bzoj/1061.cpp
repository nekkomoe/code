#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
using namespace std;
#define N 200000
#define INF 0x3f3f3f3f
 
int tot,head[N],rest[N],to[N],flow[N],cost[N],from[N];
void add(int u,int v,int c,int f){
    from[tot]=u,to[tot]=v,rest[tot]=head[u];
    flow[tot]=f,cost[tot]=c;
    head[u]=tot++;
}
void ADD(int u,int v,int c,int f){add(u,v,c,f);add(v,u,-c,0);}
int S,T,dis[N],v[N],pre[N];
queue<int>q;
int SPFA(){
    memset(dis,0x3f,sizeof(dis));
    memset(v,0,sizeof(v));
    memset(pre,-1,sizeof(pre));
    q.push(S);
    v[S]=1;
    dis[S]=0;
    while(q.size()){
        int u=q.front();q.pop();v[u]=0;
        for(int i=head[u];i!=-1;i=rest[i]){
            int vv=to[i];
            if(flow[i]&&dis[u]+cost[i]<dis[vv]){
                dis[vv]=dis[u]+cost[i];
                pre[vv]=i;
                if(!v[vv])v[vv]=1,q.push(vv);
            }
        }
    }
    return dis[T]!=INF;
}
int MCMF(){
    int f=0,c=0,mf;
    while(SPFA()){
        mf=INF;
        for(int i=pre[T];i!=-1;i=pre[from[i]])mf=min(mf,flow[i]);
        for(int i=pre[T];i!=-1;i=pre[from[i]])flow[i]-=mf,flow[i^1]+=mf;
        c+=mf*dis[T];
    }
    return c;
}
int n,m,D[N];
int main(){
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    S=0,T=n+2;
    for(int i=1;i<=n;i++){
        scanf("%d",&D[i]);
    }
    for(int i=1,x,y,z;i<=m;i++){
        scanf("%d%d%d",&x,&y,&z);
        ADD(x,y+1,z,INF);
    }
    for(int i=1;i<=n+1;i++){
        int c=D[i]-D[i-1];
        if(c>=0)ADD(S,i,0,c);
        else ADD(i,T,0,-c);
        if(i>1)ADD(i,i-1,0,INF);
    }
    printf("%d\n",MCMF());
}


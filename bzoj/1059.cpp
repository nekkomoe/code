#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <queue>
 
using namespace std;
 
const int N=201000;
int h[600],r[N],to[N],flow[N],d[N],cur[N],v[600],tot,S,T;
queue<int>q;
 
inline void ins2(int u,int v,int f){
    to[tot]=v,flow[tot]=f,r[tot]=h[u];
    h[u]=tot++;
}
 
inline void ins(int u,int v,int f){
    ins2(u,v,f);
    ins2(v,u,0);
}
 
inline bool BFS(){
    for(int i=S;i<=T;i++)v[i]=0,d[i]=-1;
    d[S]=0,v[S]=1,q.push(S);
    while(q.size()){
        int f=q.front();q.pop();
        for(int i=h[f];i!=-1;i=r[i]){
            int t=to[i];
            if(flow[i]&&!v[t]){
                d[t]=d[f]+1;
                v[t]=1;
                q.push(t);
            }
        }
    }
    return v[T];
}
 
int DFS(int x,int f){
    if(x==T||!f)return f;
    int ret=0,ff;
    for(int &i=cur[x];i!=-1;i=r[i]){
        int t=to[i];
        if(d[t]==d[x]+1&&(ff=DFS(t,min(flow[i],f)))>0){
            flow[i]-=ff,flow[i^1]+=ff,ret+=ff;
            f-=ff;
            if(!f)break;
        }
    }
    return ret;
}
 
int mf(){
    int f=0;
    while(BFS()){
        for(int i=S;i<=T;i++)cur[i]=h[i];
        f+=DFS(S,0x3f3f3f3f);
    }
    return f;
}
 
int main(){
    int tt;scanf("%d",&tt);
    while(tt--){
        tot=0;
        memset(h,-1,sizeof(h));
        int n,x;
        scanf("%d",&n);
        S=0,T=n<<1|1;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++){
                scanf("%d",&x);
                if(x)ins(i,n+j,1);
            }
        for(int i=1;i<=n;i++)ins(S,i,1),ins(n+i,T,1);
        puts(mf()==n?"Yes":"No");
    }
}


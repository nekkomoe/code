#include <iostream>
#include <algorithm>
#include <string>
#include <queue>
#include <vector>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <ctime>
 
using namespace std;
 
int n,m,k,e;
int f[200],c[200][200],un[30][200],cnt[200],d[30],v[30];
 
int to[20000],cc[20000],nxt[20000],h[20000],tot;void add(int u,int v,int c){to[++tot]=v,cc[tot]=c,nxt[tot]=h[u],h[u]=tot;}
 
void SPFA(){
    queue<int>q;
    memset(d,0x3f,sizeof(d));
    memset(v,0,sizeof(v));
    d[1]=0;
    v[1]=1;
    q.push(1);
    while(q.size()){
        int x=q.front();q.pop();
        v[x]=0;
        for(int i=h[x];i;i=nxt[i]){
            if(!cnt[to[i]]&&d[to[i]]>d[x]+cc[i]){
                d[to[i]]=d[x]+cc[i];
                if(!v[to[i]])v[to[i]]=1,q.push(to[i]);
            }
        }
    }
}
 
int main(){
    ios::sync_with_stdio(false);
    cin>>n>>m>>k>>e;
    while(e--){
        int u,v,c;cin>>u>>v>>c;add(u,v,c);add(v,u,c);
    }
    int _;cin>>_;
    while(_--){
        int p,a,b;cin>>p>>a>>b;
        for(int i=a;i<=b;i++)un[p][i]=1;
    }
 
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){
            memset(cnt,0,sizeof(cnt));
            for(int k=2;k<m;k++)
                for(int l=i;l<=j;l++)
                    if(un[k][l]){cnt[k]=1;break;}
            SPFA();
            c[i][j]=d[m]*(d[m]==0x3f3f3f3f?1:j-i+1);
        }
    }
    memset(f,0x3f,sizeof(f));
    f[0]=0;
    for(int i=1;i<=n;i++)
        for(int j=0;j<i;j++)
            f[i]=min(f[i],f[j]+c[j+1][i]+k);
    cout<<f[n]-k<<endl;
}


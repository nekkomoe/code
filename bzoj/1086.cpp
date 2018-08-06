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
 
const int N=10000;
 
int tot=1,head[N],rest[N],to[N];
void add(int u,int v){
    tot++;
    to[tot]=v;
    rest[tot]=head[u];
    head[u]=tot;
}
int n,b;
int st[N],p,bel[N],root[N],v[N],cnt;
void dfs(int x){
    v[x]=1;
    int bot=p;
    for(int i=head[x];i;i=rest[i]){
        int t=to[i];
        if(!v[t]){
            dfs(t);
            if(p-bot>=b){
                root[++cnt]=x;
                do
                    bel[st[p--]]=cnt;
                while(p!=bot);
            }
        }
    }
    st[++p]=x;
}
int main(){
    scanf("%d%d",&n,&b);
    for(int i=1;i<n;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        add(u,v);
        add(v,u);
    }
    dfs(1);
    while(p)bel[st[p--]]=cnt;
    printf("%d\n",cnt);
    for(int i=1;i<n;i++)printf("%d ",bel[i]);
    printf("%d\n",bel[n]);
    for(int i=1;i<cnt;i++)printf("%d ",root[i]);
    printf("%d\n",root[cnt]);
}

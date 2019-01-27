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
 
vector<int>G[2100000];
int n,m,c[2100000],ans;bool cmp(int a,int b){return c[a]<c[b];}
void dfs(int x){
    for(int i=0;i<G[x].size();i++)dfs(G[x][i]);
    sort(G[x].begin(),G[x].end(),cmp);
    c[x]+=G[x].size();
    for(int i=0;i<G[x].size();i++){
        if(c[x]+c[G[x][i]]-1<=m)
            c[x]+=c[G[x][i]]-1,ans++;
        else break;
    }
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++)scanf("%d",&c[i]);
    for(int i=0;i<n;i++){
        int k,v;scanf("%d",&k);
        for(int j=1;j<=k;j++)scanf("%d",&v),G[i].push_back(v);
    }
    dfs(0);
    printf("%d\n",ans);
}

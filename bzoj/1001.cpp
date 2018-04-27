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
 
int n,m;
 
 
int d[1000*1000+100];
queue<int>q;
struct{int to,cap,next;}data[7100000];
int tot,head[7100000];
 
void add(int from,int to,int cap){
    tot++;
    data[tot].to=to;
    data[tot].cap=cap;
    data[tot].next=head[from];
    head[from]=tot;
    swap(from,to);
    tot++;
    data[tot].to=to;
    data[tot].cap=cap;
    data[tot].next=head[from];
    head[from]=tot;
}
 
bool bfs(){
    memset(d,-1,sizeof(d));
    d[1]=0;
    q.push(1);
    while(q.size()){
        int x=q.front();q.pop();
        for(int i=head[x];i;i=data[i].next){
            if(data[i].cap>0&&d[data[i].to]==-1){
                d[data[i].to]=d[x]+1;
                q.push(data[i].to);
            }
        }
    }
    return d[n*m]!=-1;
}
 
int dfs(int x,int f){
    if(x==n*m)return f;
    int use=0;
    for(int i=head[x];i;i=data[i].next){
        if(data[i].cap>0&&d[data[i].to]==d[x]+1){
            int d=dfs(data[i].to,min(f-use,data[i].cap));
            data[i].cap-=d;
            data[i^1].cap+=d;
            use+=d;
            if(f==use)return f;
        }
    }
    if(use==0)d[x]=-1;
    return use;
}
 
int dinic(){
    int flow=0;
    while(bfs())flow+=dfs(1,0x3f3f3f3f);
    return flow;
}
 
int main(){
    ios::sync_with_stdio(false);
    cin>>n>>m;
    for(int i=0;i<n;i++){
        for(int j=1;j<m;j++){
            int cap;cin>>cap;
            add(j+i*m,j+i*m+1,cap);
        }
    }
    for(int i=0;i<n-1;i++){
        for(int j=1;j<=m;j++){
            int cap;cin>>cap;
            add(j+i*m,j+i*m+m,cap);
        }
    }
    for(int i=0;i<n-1;i++){
        for(int j=1;j<m;j++){
            int cap;cin>>cap;
            add(j+i*m,j+i*m+m+1,cap);
        }
    }
    cout<<dinic()<<endl;
}

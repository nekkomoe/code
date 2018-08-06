#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <map>
#include <string>
#include <vector>
using namespace std;
 
const int N=50000;
int ch[N][2],fa[N],rev[N],root[N];
 
void reverse(int x){
    if(!x)return;
    swap(ch[x][0],ch[x][1]);
    rev[x]^=1;
}
 
void down(int x){
    if(rev[x]){
        reverse(ch[x][0]);
        reverse(ch[x][1]);
        rev[x]=0;
    }
}
 
void dfs(int x){
    if(!root[x])dfs(fa[x]);
    down(x);
}
 
 
void rot(int x){
    int y=fa[x],z=fa[y],k=ch[y][1]==x;
    if(ch[x][!k])fa[ch[x][!k]]=y;
    ch[y][k]=ch[x][!k];
    fa[x]=z;
    if(root[y])root[x]=!(root[y]=0);
    else ch[z][ch[z][1]==y]=x;
    fa[y]=x,ch[x][!k]=y;
}
 
void splay(int x){
    dfs(x);
    for(int y;!root[x];rot(x)){
        if(!root[y=fa[x]])
            rot((ch[fa[y]][0]==y)==(ch[y][0]==x)?y:x);
    }
}
 
void access(int x){
    for(int y=0;x;x=fa[y=x]){
        splay(x);
        root[ch[x][1]]=1;
        root[ch[x][1]=y]=0;
    }
}
 
void makeroot(int u){
    access(u);
    splay(u);
    reverse(u);
}
 
void link(int u,int v){
    makeroot(u);
    fa[u]=v;
}
 
void cut(int u,int v){
    makeroot(u);
    splay(v);
    fa[ch[v][0]]=fa[v],fa[v]=0;
    root[ch[v][0]]=1,ch[v][0]=0;
}
 
void ask(int u,int v){
    while(fa[u])u=fa[u];
    while(fa[v])v=fa[v];
    printf("%s\n",u==v?"Yes":"No");
}
 
int n,m,u,v;
char str[100];
int main(){
    scanf("%d%d",&n,&m);
    for(int i=0;i<=n;i++)root[i]=1;
    while(m--){
        scanf("%s%d%d",str,&u,&v);
        if(str[0]=='C'){
            link(u,v);
        }else if(str[0]=='D'){
            cut(u,v);
        }else if(str[0]=='Q'){
            ask(u,v);
        }
    }
}
?

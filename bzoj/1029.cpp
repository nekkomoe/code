#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
using namespace std;
 
priority_queue<int> q;
const int N=200000;
struct T{
    int t1,t2;
    bool operator < (T b)const {
        return t2<b.t2;
    }
}t[N];
int n,ans,now;
 
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&t[i].t1,&t[i].t2);
    sort(t+1,t+1+n);
    for(int i=1;i<=n;i++){
        if(now+t[i].t1<=t[i].t2){
            now+=t[i].t1;
            q.push(t[i].t1);
            ans++;
        }else if(q.size()){
            int tp=q.top();
            if(q.top()>t[i].t1&&t[i].t1+now<=t[i].t2+q.top()){
                now-=q.top()-t[i].t1;
                q.pop();
                q.push(t[i].t1);
            }
        }
    }
    printf("%d\n",ans);
}

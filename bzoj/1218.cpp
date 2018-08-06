#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;
 
int v[5100][5100],n,r,x,y,z;
 
int main(){
    scanf("%d%d",&n,&r);
    for(int i=1;i<=n;i++){
        scanf("%d%d%d",&x,&y,&z);
        v[x+1][y+1]=z;
    }
    for(int i=1;i<=5001;i++){
        for(int j=1;j<=5001;j++){
            v[i][j]+=v[i][j-1];
        }
    }
    for(int i=1;i<=5001;i++){
        for(int j=1;j<=5001;j++){
            v[i][j]+=v[i-1][j];
        }
    }
    z=0;
    for(int i=1;i<=5001;i++){
        for(int j=1;j<=5001;j++){
            int x=min(5000,i+r-1),
                y=min(5000,j+r-1);
            z=max(z,v[x][y]-v[i-1][y]-v[x][j-1]+v[i-1][j-1]);
        }
    }
    printf("%d\n",z);
}


#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
 
using namespace std;
 
 
long long m,n;
 
long long mul(long long a,long long b){
    long long ret=1;
    a%=100003;
    while(b){
        if(b&1)ret=(ret%100003*a%100003)%100003;
        a=(a%100003*a%100003)%100003;
        b>>=1;
    }
    return ret;
}
 
int main(){
    scanf("%lld%lld",&m,&n);
    printf("%lld\n",((((mul(m,n)%100003-(m%100003)*(mul(m-1,n-1)%100003))%100003)+100003)%100003));
}


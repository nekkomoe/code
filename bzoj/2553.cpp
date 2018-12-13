#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 110;

int cnt, n, len, alp; char str[N];

struct Mat {
    long double a[N][N];
    Mat() { memset(a, 0, sizeof a); }
    long double *operator [] (int x) { return a[x]; }
    Mat operator * (Mat b) {
        Mat c;
        for(int i = 0 ; i <= cnt ; ++ i)
            for(int j = 0 ; j <= cnt ; ++ j)
                for(int k = 0 ; k <= cnt ; ++ k)
                    c[i][j] = (c[i][j] + a[i][k] * b[k][j]);
        return c;
    }
} mat;

Mat pw(Mat a, ll b) {
    Mat r;
    for(int i = 0 ; i <= cnt ; ++ i) r[i][i] = 1;
    for( ; b ; b >>= 1, a = a * a)
        if(b & 1)
            r = r * a;
    return r;
}

int ch[N][30], poi[N], fail[N], vis[N];

void ins() {
    int x = 0;
    for(int i = 1 ; str[i] ; ++ i) {
        int c = str[i] - 'a';
        if(!ch[x][c]) ch[x][c] = ++ cnt;
        x = ch[x][c];
    }
    poi[x] = 1;
}

void build() {
    
    queue<int> q;
    for(int i = 0 ; i < alp ; ++ i)
        if(ch[0][i])
            q.push(ch[0][i]);
    while(q.size()) {
        int u = q.front(); q.pop();
        for(int i = 0 ; i < alp ; ++ i) {
            if(!ch[u][i]) {
                ch[u][i] = ch[fail[u]][i];
            } else {
                fail[ch[u][i]] = ch[fail[u]][i];
                q.push(ch[u][i]);
            }
            poi[u] |= poi[fail[u]];
        }
    }
    
    
    long double p = (long double) 1 / alp;
    
    for(int u = 0 ; u <= cnt ; ++ u) {
        for(int c = 0 ; c < alp ; ++ c) {
            if(poi[ch[u][c]]) {
                mat[u][cnt + 1] += p;
                mat[u][0] += p;
            } else {
                mat[u][ch[u][c]] += p;
            }
        }
    }
    mat[cnt + 1][cnt + 1] = 1;
}

int main() {
    scanf("%d%d%d", &n, &len, &alp);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%s", str + 1);
        ins();
    }
    build();
    ++ cnt;
    
    printf("%.7Lf\n", pw(mat, len)[0][cnt]);
} 


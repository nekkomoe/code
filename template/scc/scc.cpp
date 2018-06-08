int head[N], rest[N], to[N], tot;

void add(int u, int v) {
	to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
}

int dfn[N], low[N], clk;

stack<int> s;

void dfs(int u) {
    dfn[u] = low[u] = ++ clk;
    s.push(u);
    ins[u] = 1;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(!dfn[v]) {
            dfs(v);
            low[u] = min(low[u], low[v]);
        } else if(ins[v]){
            low[u] = min(low[u], dfn[v]);
        }
    }
    if(dfn[u] == low[u]) {
        cnt ++;
        int v;
        do {
            v = s.top();
            s.pop();
            ins[v] = 0;
            id[v] = cnt;
            vec[cnt].push_back(v);
        } while(u != v);
    }
}
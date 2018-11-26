const int MAXN = 4e5, INF = 1e9;
int gg[111][111], fl[111];
int n, m, S, T, E;
int head[MAXN], to[MAXN], cap[MAXN], nxt[MAXN], cost[MAXN];
int was[MAXN], dd[MAXN], pp[MAXN], qh, qt, qq[MAXN];

void addEdge(int a, int b, int cp, int cs) {
    to[E] = b, cap[E] = cp, cost[E] = cs;
    nxt[E] = head[a], head[a] = E++;
    to[E] = a, cap[E] = 0, cost[E] = -cs;
    nxt[E] = head[b], head[b] = E++;
}

bool SPFA() {
    fill(was, was + MAXN, 0);
    fill(dd, dd + MAXN, INF);
    was[S] = 1, dd[S] = 0, qh = qt = 0, qq[qt++] = S;
    while(qh != qt) {
        int v = qq[qh++];
        if(qh == MAXN) qh = 0;
        was[v] = 0;
        for(int id = head[v]; id != -1; id = nxt[id]) {
            int nv = to[id];
            if(cap[id] > 0 && dd[nv] > dd[v] + cost[id]) {
                dd[nv] = dd[v] + cost[id];
                if(!was[nv]) {
                    was[nv] = 1, qq[qt++] = nv;
                    if(qt == MAXN) qt = 0; 
                }
                pp[nv] = id;
            }
        }
    }
    return dd[T] != INF;
}

pair < int, int > mincost() {
    int flow = 0, cost_flow = 0;
    while(SPFA()) {
        int add = INF, add_cost = 0;
        for(int i = T; i != S; i = to[pp[i] ^ 1]) {
            add_cost += cost[pp[i]];
            add = min(add, cap[pp[i]]);
        }
        flow += add;
        cost_flow += add * add_cost;
        for(int i = T; i != S; i = to[pp[i] ^ 1]) {
            cap[pp[i]] -= add;
            cap[pp[i] ^ 1] += add;
        }
    }
    return { flow, cost_flow };
}
#include <bits/stdc++.h>
#define N 100010
#define M 220

using namespace std;

int n, m, k, scc, cnt;
int low[N], num[N], pre[N], d[N], a[N];
long long f[N][M], val[N][M], temp[N];
vector < int > ke[N], g[N], vC[N];

struct stack {
    int size, st[N];
    stack () { size = 0; }
    bool empty() { return size == 0; }
    void push(int u) { st[++size] = u; }
    int pop() { return st[size--]; }
} s;

void visit(int u) {
    num[u] = low[u] = ++cnt;
    s.push(u);
    for (int i = 0; i < ke[u].size(); i++) {
        int v = ke[u][i];
        if ( pre[v] ) continue;
        if ( num[v] ) low[u] = min(low[u], num[v]);
        else {
            visit(v);
            low[u] = min(low[u], low[v]);
        }
    }
    if ( num[u] == low[u] ) {
        scc++;
        while ( !s.empty() ) {
            int v = s.pop();
            pre[v] = scc;
            vC[scc].push_back(a[v]);
            if ( v == u ) break;
        }
    }
}

void dfs(int u) {
    if ( d[u] ) return;
    d[u] ++;
    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        dfs(v);
        for (int j = 0; j <= k; j++)
            f[u][j] = max(f[u][j], f[v][j]);
    }
    for (int i = 0; i <= k; i++) temp[i] = f[u][i];
    for (int i = 0; i < vC[u].size(); i++)
        for (int j = 0; j <= k; j++) {
            if ( i + j > k ) break;
            f[u][i + j] = max(f[u][i + j], val[u][i] + temp[j]);
        }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    //freopen("main.inp", "r", stdin);
    //freopen("main.out", "w", stdout);

    int test; cin >> test;
    while ( test-- ) {
        cin >> n >> m >> k;
        for (int i = 1; i <= n; i++) {
            ke[i].clear(); g[i].clear(); vC[i].clear();
            num[i] = low[i] = pre[i] = d[i] = 0;
            for (int j = 0; j <= k; j++)
                f[i][j] = val[i][j] = 0;
        }
        scc = cnt = 0;
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= m; i++) {
            int u, v; cin >> u >> v;
            ke[u].push_back(v);
        }
        for (int i = 1; i <= n; i++)
            if ( !num[i] ) visit(i);
        for (int i = 1; i <= n; i++)
            for (int j = 0; j < ke[i].size(); j++) {
                int v = ke[i][j];
                if ( pre[i] != pre[v] ) g[pre[i]].push_back(pre[v]);
            }
        for (int i = 1; i <= scc; i++) {
            sort(vC[i].begin(), vC[i].end());
            int siz = vC[i].size();
            for (int j = 0; j <= min(k, siz - 1); j++)
                val[i][j] = 1LL * (siz - j) * vC[i][j];
        }
        for (int i = 1; i <= scc; i++) dfs(i);
        long long res = 0;
        for (int i = 1; i <= scc; i++)
            for (int j = 0; j <= k; j++)
                res = max(res, f[i][j]);
        cout << (res % 1000000021) << "\n";
    }

    return 0;
}

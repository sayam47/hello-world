#include<bits/stdc++.h>

#define el cout<<"\n"
#define file ""
#define	f0(i,n) for(int i=0;i<n;i++)
#define f1(i,n) for(int i=1;i<=n;i++)
#define maxn 100005

using namespace std;
int n, m, k, cnt, low[maxn], num[maxn], dd[maxn], cntSCC, par[maxn], t, c[maxn];
long long g[maxn][202], f[maxn][202], h[202], ans;
stack <int> st;
vector <int> a[maxn], b[maxn], val[maxn];
void dfs_scc(int u)
{
    low[u]=num[u]=++cnt;
    st.push(u);
    for (auto v:a[u])
    {
        if (num[v]) low[u]= min (low[u], num[v]);
        else
        {
            dfs_scc(v);
            low[u]=min(low[u], low[v]);
        }
    }
    if (num[u]==low[u])
    {
        ++cntSCC;
        int v;
        do
        {
            v=st.top();
            st.pop();
            low[v]=num[v]=1e9;
            par[v]=cntSCC;
            val[cntSCC].push_back(c[v]);
        }
        while (u!=v);
    }
}
void dfs_make_graph(int u)
{
    dd[u]=1;
    for (auto v:a[u])
    {
        if (!dd[v]) dfs_make_graph(v);
        if (par[u]!=par[v]) b[par[u]].push_back(par[v]);
    }
}
void dfs_dp(int u)
{
    dd[u]=1;
    for (auto v:b[u])
    {
        if (!dd[v]) dfs_dp(v);
        f0 (i, k+1) f[u][i]=max(f[u][i], f[v][i]);
    }
    f0(i, k+1) h[i]=f[u][i];
    f0(i, val[u].size()+1)
            for(int j=0;j+i<=k;j++)
                f[u][i+j]=max(f[u][i+j],g[u][i]+h[j]);
}
void init()
{
    f1 (i, cntSCC)
    {
        sort (val[i].begin(), val[i].end());
        int sz=val[i].size();
        f0 (j, min(k, sz-1)+1)
            g[i][j]=1ll*(sz-j)*val[i][j];
    }
}
void reset_all()
{
    f1 (i, n)
    {
        par[i]=low[i]=num[i]=dd[i]=0;
        a[i].clear(); b[i].clear(); val[i].clear();
        f0 (j, k+1) f[i][j]=g[i][j]=0;
    }
    cnt = cntSCC = ans = 0;
    return;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ///freopen(file".inp","r",stdin);
    ///freopen(file".out","w",stdout);
    cin >> t;
    while (t--)
    {
        cin >> n >> m >> k;
        f1 (i, n) cin >> c[i];
        f1 (i, m)
        {
            int u, v;
            cin >> u >> v;
            a[u].push_back(v);
        }
        f1 (i, n) if (!num[i]) dfs_scc(i);
        memset(dd,0,sizeof(dd));
        f1 (i, n) if (!dd[i]) dfs_make_graph(i);
        init();
        memset(dd,0,sizeof(dd));
        f1 (i, cntSCC) if (!dd[i]) dfs_dp(i);
        f1 (i, cntSCC)
            f0 (j, k+1) ans = max(ans, f[i][j]);
        cout << ans % 1000000021; el;
        reset_all();
    }
    return 0;
}

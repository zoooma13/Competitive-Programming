/**
let's root the tree at e.
if all edges from root to given city aren't destroyed then you can escape.
else check for the nearest shop in the subtree rooted at u where edge(u ,v) 
is the nearest destroyed edge to given city and u is the nearest vertex to the city.
we can solve this problem using binary lifting where we store for each node the 
minimum distance shop to it and to its power of 2 parents.

time complexity O(N*logN)
*/

#include <bits/stdc++.h>
using namespace std;

#define MAX_N 100005
#define LOG_N 18
#define pii pair<int ,int>
#define fi first
#define se second
#define INF 0x3f3f3f3f3f3f3f3f

int n ,s ,q ,e;
int a ,b ,w;
pii edg[MAX_N];
vector <pii> adj[MAX_N];
bool has_shop[MAX_N];

int dep[MAX_N] ,anc[LOG_N][MAX_N];
long long to[MAX_N] ,nrshop[MAX_N] ,mipath[LOG_N][MAX_N];

void dfs(int u)
{
    nrshop[u] = (has_shop[u] ? 0 : INF);
    for(auto v : adj[u]) if(v.fi != anc[0][u])
    {
        to[v.fi] = to[u]+v.se;
        dep[v.fi] = dep[u]+1;
        anc[0][v.fi] = u;
        dfs(v.fi);
        nrshop[u] = min(nrshop[u] ,nrshop[v.fi]+v.se);
    }
    mipath[0][u] = nrshop[u]-to[u];
}
int lca(int u ,int v)
{
    if(dep[u] < dep[v])
        swap(u ,v);
    int diff = dep[u]-dep[v];
    for(int j=0; j<LOG_N; j++)
        if(diff&(1<<j))
            u = anc[j][u];
    if(u == v)
        return u;
    for(int j=LOG_N-1; ~j; j--)
        if(anc[j][u] != anc[j][v])
            u = anc[j][u] ,v = anc[j][v];
    return anc[0][u];
}

int main()
{
    scanf("%d%d%d%d",&n,&s,&q,&e);
    for(int i=1; i<n; i++){
        scanf("%d%d%d",&a,&b,&w);
        adj[a].push_back({b ,w});
        adj[b].push_back({a ,w});
        edg[i] = {a ,b};
    }
    for(int i=0; i<s; i++)
        scanf("%d",&w) ,has_shop[w] = 1;

    memset(anc ,-1 ,sizeof anc);
    memset(mipath ,INF ,sizeof mipath);
    dfs(e);
    for(int j=1; j<LOG_N; j++)
    for(int i=1; i<=n; i++)
        if(~anc[j-1][i]){
            anc[j][i] = anc[j-1][anc[j-1][i]];
            mipath[j][i] = min(mipath[j-1][i] ,mipath[j-1][anc[j-1][i]]);
        }

    while(q--){
        scanf("%d%d",&a,&b);
        int u = edg[a].fi ,v = edg[a].se;
        if(dep[u] < dep[v])
            swap(u ,v);
        if(lca(u ,b) != u)
            printf("escaped\n");
        else{
            long long ans = INF;
            int diff = dep[b] - dep[u]+1; v = b;
            for(int j=LOG_N-1; ~j; j--)
                if(diff&(1<<j)){
                    ans = min(ans ,mipath[j][v]);
                    v = anc[j][v];
                }
            ans += to[b];
            if(ans > 1e18)
                printf("oo\n");
            else
                printf("%lld\n",ans);
        }
    }
}

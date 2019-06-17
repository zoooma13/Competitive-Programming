/**
tags : tree ,HLD
time complexity : O(q*log^2(n))
*/

#include <bits/stdc++.h>
using namespace std;

#define MAX_N 100005

int n ,q;
int a ,b;
vector <int> adj[MAX_N];

int subsz[MAX_N] ,par[MAX_N];
void dfs_sz(int u){
    subsz[u] = 1;
    for(int&v : adj[u]){
        adj[v].erase(find(adj[v].begin() ,adj[v].end() ,u));
        par[v] = u;
        dfs_sz(v);
        subsz[u] += subsz[u];
    }
    sort(adj[u].begin() ,adj[u].end() ,[](int&i ,int&j){
        return subsz[i] > subsz[j];
    });
}
int st[MAX_N] ,en[MAX_N] ,nxt[MAX_N] ,idx = 0;
set <pair<int ,int>> mi_path[MAX_N];
void dfs_hld(int u){
    if(!adj[u].empty())
        nxt[adj[u][0]] = nxt[u];
    st[u] = idx++;
    for(int&v : adj[u])
        dfs_hld(v);
    en[u] = idx-1;
}
bool ispar(int p ,int u){
    return (st[p] <= st[u] && st[u] <= en[p]);
}

int main()
{
    scanf("%d%d",&n,&q);
    for(int i=1; i<n; i++){
        scanf("%d%d",&a,&b);
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs_sz(1); par[1] = 1;
    iota(nxt ,nxt+n+1 ,0);
    dfs_hld(1);
    ///a chain = (st[nxtu] ,st[u])

    while(q--){
        scanf("%d%d",&a,&b);
        if(a == 0){
            auto p = make_pair(st[b] ,b);
            if(mi_path[nxt[b]].count(p))
                mi_path[nxt[b]].erase(p);
            else
                mi_path[nxt[b]].insert(p);
        }else{
            int ans = -1;
            while(b != 1){
                if(!mi_path[nxt[b]].empty()){
                    auto mi = *mi_path[nxt[b]].begin();
                    if(mi.first <= st[b])
                        ans = mi.second;
                }
                b = par[nxt[b]];
            }
            if(!mi_path[1].empty() && mi_path[1].begin()->second == 1)
                printf("%d\n",1);
            else
                printf("%d\n",ans);
        }
    }
}

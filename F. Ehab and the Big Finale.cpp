/**
editorial : https://codeforces.com/blog/entry/67388
tags : HLD ,interactive
*/

#include <bits/stdc++.h>
using namespace std;

#define MAX_N 200005

int qs = 0;
int d(int u){
    assert(++qs <= 36);
    int ret;
    cout << "d " << u << endl;
    cin >> ret;
    return ret;
}
int s(int u){
    assert(++qs <= 36);
    int ret;
    cout << "s " << u << endl;
    cin >> ret;
    return ret;
}

int n;
int a ,b;
vector <int> adj[MAX_N];

int x_depth;
int sz[MAX_N] ,en[MAX_N] ,depth[MAX_N] ,par[MAX_N];
bool can[MAX_N];
void dfs(int u ,int p=-1 ,int d=0){
    sz[u] = 1 ,depth[u] = d ,par[u] = p;
    if(d == x_depth){
        can[u] = 1;
        adj[u].clear();
        return;
    }

    vector <int> ok;
    for(int&v : adj[u]) if(v != p){
        dfs(v ,u ,d+1);
        if(can[v]){
            sz[u] += sz[v] ,can[u] = 1;
            ok.push_back(v);
        }
    }

    sort(ok.begin() ,ok.end() ,[](int&i ,int&j){
        return sz[i] > sz[j];
    });
    swap(adj[u] ,ok);
}
int get(int u){
    if(en[u])
        return en[u];
    return en[u] = (adj[u].empty() ? u : get(adj[u].front()));
}

int main()
{
    scanf("%d",&n);
    for(int i=1; i<n; i++){
        scanf("%d%d",&a,&b);
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    x_depth = d(1) ,dfs(1);
    for(int i=1; i<=n; i++)
        if(can[i])
            en[i] = get(i);

    int root = 1;
    while(true){
        int to = en[root] ,di = depth[to]-(x_depth+depth[to]-d(to))/2;
        ///depth[x]+depth[to]-dist = 2*depth[lca]
        if(!di){
            cout << "! " << to << endl;
            return 0;
        }
        while(di--)
            to = par[to];
        root = s(to);
    }
}

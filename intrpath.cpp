/**
tags : HLD ,euler tour
time complexity : O(nlogn)
*/

#include <bits/stdc++.h>
using namespace std;

#define MAX_N 300005

int t;
int n ,q;
int a ,b;
vector <int> adj[MAX_N];

long long tot[MAX_N];
int sz[MAX_N] ,par[MAX_N];
void pre(int u){
    sz[u] = 1;
    for(int&v : adj[u]){
        adj[v].erase(find(adj[v].begin() ,adj[v].end() ,u));
        pre(v);
        par[v] = u ,sz[u] += sz[v];
    }
    tot[u] = 0LL;
    for(int&v : adj[u])
        tot[u] += 1LL*sz[v]*(sz[u]-sz[v]-1);
    tot[u] = tot[u]/2 + sz[u];
    sort(adj[u].begin() ,adj[u].end() ,[](int&i ,int&j){
        return sz[i] > sz[j];
    });
}
int st[MAX_N] ,en[MAX_N] ,nxt[MAX_N] ,node[MAX_N] ,idx;
void dfs(int u){
    node[idx] = u ,st[u] = idx++;
    if(!adj[u].empty())
        nxt[adj[u][0]] = nxt[u];
    for(int v : adj[u])
        dfs(v);
    en[u] = idx-1;
}
bool ispar(int p ,int u){
    return st[p] <= st[u] && st[u] <= en[p];
}

long long path_sum[MAX_N];
long long bld_path(){
    path_sum[0] = 0;
    for(int p,a,i=0; i<n; i++){
        p = node[i] ,a = adj[p].front();
        path_sum[i+1] = path_sum[i] + tot[p] - (sz[a] + 1LL*sz[a]*(sz[p]-sz[a]-1));
    }
}
long long qry_path(int l ,int r ,int lc){
    return path_sum[r] - path_sum[l] + tot[node[r]] - (sz[lc] + 1LL*sz[lc]*(sz[node[r]]-sz[lc]-1));
}

int main()
{
    scanf("%d",&t);
    while(t--){
        idx = 0;
        for(int i=0; i<=n; i++)
            adj[i].clear();

        scanf("%d%d",&n,&q);
        for(int i=1; i<n; i++){
            scanf("%d%d",&a,&b);
            adj[a].push_back(b);
            adj[b].push_back(a);
        }

        iota(nxt ,nxt+n+1 ,0);
        par[1] = 1;
        pre(1) ,dfs(1);
        bld_path();

        while(q--){
            scanf("%d%d",&a,&b);
            if(ispar(b ,a))
                swap(a ,b);

            if(a == b){
                printf("%lld\n",tot[a]+1LL*(n-sz[a])*(sz[a]));
            }
            else if(ispar(a ,b)){
                long long ans = tot[b];
                int lb = b;
                b = par[b];
                while(!ispar(nxt[b] ,a)){
                    ans += qry_path(st[nxt[b]] ,st[b] ,lb);
                    lb = nxt[b] ,b = par[nxt[b]];
                }
                if(a != b){
                    ans += qry_path(st[a]+1 ,st[b] ,lb);
                    lb = node[st[a]+1];
                }
                ans += tot[a] - (sz[lb] + 1LL*sz[lb]*(sz[a]-sz[lb]-1));
                ans += 1LL*(n-sz[a])*(sz[a]-sz[lb]);
                printf("%lld\n",ans);
            }
            else{
                long long ans = tot[a] + tot[b];
                int la = a ,lb = b;
                a = par[a] ,b = par[b];
                while(!ispar(nxt[a] ,b)){
                    ans += qry_path(st[nxt[a]] ,st[a] ,la);
                    la = nxt[a] ,a = par[nxt[a]];
                }
                while(nxt[a] != nxt[b]){
                    ans += qry_path(st[nxt[b]] ,st[b] ,lb);
                    lb = nxt[b] ,b = par[nxt[b]];
                }

                if(ispar(b ,a))
                    swap(a ,b) ,swap(la ,lb);
                if(a != b){
                    ans += qry_path(st[a]+1 ,st[b] ,lb);
                    lb = node[st[a]+1];
                }

                ans += tot[a];
                ans += 1LL*(n-sz[a])*(sz[a]-(sz[la]+sz[lb]));
                ans -= 1LL*sz[la]*(sz[a]-sz[la]-1) + sz[la];
                ans -= 1LL*sz[lb]*(sz[a]-sz[lb]-1) + sz[lb];
                ans += 1LL*sz[la]*sz[lb];
                printf("%lld\n",ans);
            }
        }
    }
}

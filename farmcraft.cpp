/**
once we enter a subtree we have to visit all its nodes before exiting it
so the problem can be simplified to find what is the optimal order to visit a node's children to minimize the max time
we have to store for each vertex its the minimal max time in its subtree and its subtree size.
for vertex u's children we have their sizes(s_i) and max ready time(t_i) 
we want to order them such that max_i<n_{ch_i.t + sum_j<i_{ch_j.s*2} + 1} is minimal
its better to visit node a before b if (a.s+b.t < b.s+a.t)
so we sort them according to this comparator and calculate the max time in this subtree.

time complexity : O(N*logN)
*/

#include <bits/stdc++.h>
using namespace std;

#define MAX_N 500005
#define pii pair<int ,int>
#define s first
#define t second

int n;
int c[MAX_N];
vector <int> adj[MAX_N];
int dp[MAX_N] ,sz[MAX_N];

int mini(vector<pii>&ch){
    sort(ch.begin() ,ch.end() ,[](pii i ,pii j){
        return i.t+j.s < j.t+i.s;
    });
    int ret = 0 ,tt = 0;
    for(pii c : ch){
        ret = max(ret ,c.s+tt+1);
        tt += c.t;
    }
    return ret;
}
void dfs(int u ,int p=-1){
    sz[u] = 1;
    vector <pii> ch;
    for(int v : adj[u]) if(v != p){
        dfs(v ,u);
        sz[u] += sz[v];
        ch.push_back({dp[v] ,2*sz[v]});
    }
    dp[u] = max(c[u] ,mini(ch));
}

int main()
{
    scanf("%d",&n);
    for(int i=1; i<=n; i++)
        scanf("%d",&c[i]);
    for(int a,b,i=1; i<n; i++){
        scanf("%d%d",&a,&b);
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(1);
    printf("%d\n",max(c[1]+2*n-2 ,dp[1]));
}

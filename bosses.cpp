/**
problem is given the possible parents of each vertex form a tree with minimum total sum of subtrees sizes.
a vertex donates to the total sum by exactly its depth where the depth of root = 1
we can solve this problem by doing a simple bfs starting from every vertex and taking the minimum of them.

time complexity : O(N^2 * logK)
*/

#include <bits/stdc++.h>
using namespace std;

#define MAX_N 5003

int n ,m;
vector <int> adj[MAX_N];

int bfs(int s){
    int ret = 0;
    queue <int> nxt; nxt.push(s);
    vector <int> dist(n+1 ,-1); dist[s] = 1;
    while(!nxt.empty()){
        int u = nxt.front(); nxt.pop();
        ret += dist[u];
        for(int v : adj[u])
            if(!~dist[v])
                nxt.push(v) ,dist[v] = dist[u]+1;
    }
    if(count(dist.begin() ,dist.end() ,-1) > 1)
        return 1e9;
    else
        return ret;
}

int main()
{
    scanf("%d",&n);
    for(int i=1; i<=n; i++){
        scanf("%d",&m);
        for(int x,j=0; j<m; j++){
            scanf("%d",&x);
            adj[x].push_back(i);
        }
    }

    int ans = 1e9;
    for(int i=1; i<=n; i++)
        ans = min(ans ,bfs(i));

    printf("%d\n",ans);
}

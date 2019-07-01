#include <bits/stdc++.h>
using namespace std;

#define MAX_N 100005

int n ,m;
int a ,b;
vector <int> adj[MAX_N] ,radj[MAX_N];

vector <int> ord;
bool vis[MAX_N];
void toposort(int u){
    vis[u] = 1;
    for(int&v : adj[u])
        if(!vis[v])
            toposort(v);
    ord.push_back(u);
}
vector <int> nodes;
void getnodes(int u){
    nodes.push_back(u);
    vis[u] = 1;
    for(int&v : radj[u])
        if(!vis[v])
            getnodes(v);
}

int dag_n ,dag_m ,st_node;
int node_we[MAX_N];
vector <int> dag_adj[2][MAX_N];
void bld_dag()
{
    memset(vis ,0 ,sizeof vis);
    for(int i=1; i<=n; i++)
        if(!vis[i])
            toposort(i);

    int scc_idx = 1;
    memset(vis ,0 ,sizeof vis);
    vector <int> belong_to(n+1 ,0);
    while(!ord.empty()){
        int u = ord.back(); ord.pop_back();
        if(!vis[u]){
            nodes.clear();
            getnodes(u);

            vector <int> u_adj;
            for(int&u : nodes){
                belong_to[u] = scc_idx;
                for(int&v : adj[u])
                    u_adj.push_back(v);
                if(u == 1)
                    st_node = scc_idx;
            }

            /*cout << scc_idx << " : ";
            for(int&u : nodes)
                cout << u << ' ';
            cout << " = " << node_we[scc_idx] << endl;*/

            node_we[scc_idx] = nodes.size();
            swap(dag_adj[0][scc_idx] ,u_adj);
            scc_idx++;
        }
    }

    dag_n = scc_idx-1;
    for(int i=1; i<=dag_n; i++){
        for(int&v : dag_adj[0][i])
            v = belong_to[v];

        sort(dag_adj[0][i].begin() ,dag_adj[0][i].end());
        dag_adj[0][i].resize(unique(dag_adj[0][i].begin() ,dag_adj[0][i].end())-dag_adj[0][i].begin());

        auto it = find(dag_adj[0][i].begin() ,dag_adj[0][i].end() ,i);
        if(it != dag_adj[0][i].end())
            dag_adj[0][i].erase(it);

        dag_m += dag_adj[0][i].size();
    }

    for(int u=1; u<=dag_n; u++)
    for(int&v : dag_adj[0][u])
        dag_adj[1][v].push_back(u);
}

int dp[2][MAX_N];
int dfs(int u ,bool rev){
    int&ret = dp[rev][u];
    if(~ret)
        return ret;
    if(u == st_node)
        return ret=node_we[u];

    ret = -1e9;
    for(int&v : dag_adj[rev][u])
        ret = max(ret ,dfs(v ,rev));
    ret += node_we[u];
    return ret;
}

int main()
{
    freopen("grass.in" ,"r" ,stdin);
    freopen("grass.out" ,"w" ,stdout);

    scanf("%d%d",&n,&m);
    for(int i=0; i<m; i++){
        scanf("%d%d",&a,&b);
        adj[a].push_back(b);
        radj[b].push_back(a);
    }

    bld_dag();

    /*for(int i=1; i<=dag_n; i++)
    {
        cout << i << " : ";
        for(int&u : dag_adj[i])
            cout << u << ' ';
        cout << endl;
    }*/
    memset(dp ,-1 ,sizeof dp);
    for(int i=1; i<=dag_n; i++)
        dfs(i ,0) ,dfs(i ,1);

    /*for(int i=1; i<=dag_n; i++)
        cout << i << " ::::: " << dp[0][i] << endl;
    for(int i=1; i<=dag_n; i++)
        cout << i << " ::::: " << dp[1][i] << endl;*/

    int ans = node_we[st_node];
    for(int u=1; u<=dag_n; u++)
    for(int&v : dag_adj[0][u])
    {
        //cout << u << ' ' << v << " = " << max(dp[0][u]+dp[1][v] ,dp[1][u]+dp[0][v])-node_we[st_node] << endl;
        ans = max(ans ,max(dp[0][u]+dp[1][v] ,dp[1][u]+dp[0][v])-node_we[st_node] );
    }

    printf("%d\n",ans);
}

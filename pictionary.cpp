/**
*/

#include <bits/stdc++.h>
using namespace std;

#define MAX_N 100005
#define LOG_N 20

int N ,M ,Q;
int A ,B;

int Parent[MAX_N];
int Find(int U){
    return Parent[U] = (Parent[U] == U ? U : Find(Parent[U]));
}
bool Union(int U ,int V){
    U = Find(U) ,V = Find(V);
    if(U != V){
        Parent[U] = V;
        return 1;
    }
    return 0;
}

#define Edge pair<int ,int>
#define to first
#define we second
vector < Edge > Adj[MAX_N];
int depth[MAX_N];
int Anc[LOG_N][MAX_N] ,Ed[LOG_N][MAX_N];

void DFS(int V){
    for(auto&i : Adj[V])
        if(i.to != Anc[0][V]){
            depth[i.to]  = depth[V]+1;
            Anc[0][i.to] = V;
            Ed[0][i.to] = i.we;
            DFS(i.to);
        }
}
void BuildLCA(){
    memset(Anc ,-1 ,sizeof Anc);
    depth[1] = 0;   DFS(1);

    for(int j=1; j<LOG_N; j++)
    for(int i=1; i<=N; i++)
        if(Anc[j-1][i] != -1)
            Anc[j][i] = Anc[j-1][ Anc[j-1][i] ],
            Ed[j][i] = max(Ed[j-1][i] ,Ed[j-1][ Anc[j-1][i] ]);
}
int LCA(int U ,int V){
    if(depth[U] > depth[V])
        swap(U ,V);

    int Diff = depth[V] - depth[U];
    for(int i=0; i<LOG_N; i++)
        if((Diff >> i)&1)
            V = Anc[i][V];
    if(U == V)
        return U;

    for(int i=LOG_N-1; i>=0; i--)
        if(Anc[i][V] != Anc[i][U])
            U = Anc[i][U] ,V = Anc[i][V];
    return Anc[0][U];
}

int mato(int U ,int lca){
    int ma = 0;
    for(int i=LOG_N-1; i>=0; i--)
        if(depth[U] - depth[lca] >= (1<<i)){
            ma = max(ma ,Ed[i][U]);
            U = Anc[i][U];
        }
    return ma;
}

int main()
{
    cin >> N >> M >> Q;

    iota(Parent ,Parent+N+1 ,0);
    for(int i=M; i; i--)
    {
        for(int j=i+i; j<=N; j+=i)
            if(Union(i ,j))
                Adj[i].push_back({j ,M-i+1}),
                Adj[j].push_back({i ,M-i+1});
    }

    BuildLCA();
    for(int i=0; i<Q; i++)
    {
        cin >> A >> B;
        int lc = LCA(A ,B);
        cout << max(mato(A ,lc) ,mato(B ,lc)) << endl;
    }
}

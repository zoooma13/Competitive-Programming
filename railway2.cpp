/**

*/

#include <bits/stdc++.h>
using namespace std;

#define MAX_N 100005
#define MAX_M 50005
#define LOG_N 18
#define FL (P<<1)|1
#define FR (P<<1)+2

int N ,M ,K;
int S ,A ,B;
vector <pair<int ,int> > Adj[MAX_N];

/**START :: LCA binary lifting**/
int Depth[MAX_N];
int Anc[LOG_N][MAX_N];
void DFS(int V){
    for(auto&i : Adj[V])
        if(i.first != Anc[0][V]){
            Depth[i.first]  = Depth[V]+1;
            Anc[0][i.first] = V;
            DFS(i.first);
        }
}
void BuildLCA(){
    memset(Anc ,-1 ,sizeof Anc);
    Depth[1] = 1;   DFS(1);

    for(int j=1; j<LOG_N; j++)
        for(int i=1; i<=N; i++)
            if(Anc[j-1][i] != -1)
                Anc[j][i] = Anc[j-1][ Anc[j-1][i] ];
}
int LCA(int U ,int V){
    if(Depth[U] > Depth[V])
        swap(U ,V);

    int Diff = Depth[V] - Depth[U];
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
/**END :: LCA binary lifting**/

/**START :: Lazy Segment Tree**/
int Tree[4*MAX_N];
void Update(int QL ,int QR ,int Val ,int L=0 ,int R=N ,int P=0){
    if(QR < L || R < QL)
        return;
    if(QL <= L && R <= QR){
        Tree[P] += Val;
        return;
    }
    int Mid = (L+R)>>1;
    Update(QL ,QR ,Val ,L ,Mid ,FL);
    Update(QL ,QR ,Val ,Mid+1 ,R ,FR);
}
int Get(int idx ,int L=0 ,int R=N ,int P=0){
    if(L == R)
        return Tree[P];
    int Mid = (L+R)>>1;
    if(idx <= Mid)
        return Tree[P] + Get(idx ,L ,Mid ,FL);
    else
        return Tree[P] + Get(idx ,Mid+1 ,R ,FR);
}
/**END :: Lazy Segment Tree**/

int bef[MAX_M];
vector <int> bad[MAX_N];
vector <int> Ans;
void Solve(int Q ,int D ,int ed)
{
    for(int&i : bad[Q]){
        if(bef[i])
            Update(Depth[LCA(bef[i] ,Q)]+1 ,D ,1);
        bef[i] = Q;
    }

    for(auto&i : Adj[Q])
        if(i.first != Anc[0][Q])
            Solve(i.first ,D+1 ,i.second);

    int x = Get(D);
    if(x >= K)
        Ans.push_back(ed);

    Update(D ,D ,-x);
}

int main()
{
    scanf("%d%d%d",&N,&M,&K);
    for(int i=1; i<N; i++){
        scanf("%d%d",&A,&B);
        Adj[A].emplace_back(B ,i);
        Adj[B].emplace_back(A ,i);
    }

    BuildLCA();

    for(int i=0; i<M; i++){
        scanf("%d",&S);
        int lca = 0;
        for(int j=0; j<S; j++)
        {
            scanf("%d",&A);
            bad[A].push_back(i);
            lca = (lca ? LCA(lca ,A) : A);
        }
        bad[lca].push_back(i);
    }

    Solve(1 ,1 ,-1);
    sort(Ans.begin() ,Ans.end());
    printf("%d\n",Ans.size());
    for(int&i : Ans)
        printf("%d ",i);
    printf("\n");
}

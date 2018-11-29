/**
first solution : https://github.com/zoooma13/Competitive-Programming/blob/master/pictionary.cpp

we don't really need to use binary lifting to solve the problem.

since we only add edges between number and its multiples ,
then the depth of the tree is at most logN.

so we can just go to nodes' parent iteratively until they are in
the same node and calculate the maximum edge on the path.

but because of the constant factor in the first code this
solution works faster.

time complexity : O(N*log(M) + Q*log(N))
*/

#include <bits/stdc++.h>
using namespace std;

#define MAX_N 100005

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
int depth[MAX_N] ,par[MAX_N] ,ed[MAX_N];
void DFS(int V){
    for(auto&i : Adj[V])
        if(i.to != par[V])
        {
            depth[i.to] = depth[V]+1;
            par[i.to] = V;
            ed[i.to] = i.we;
            DFS(i.to);
        }
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

    DFS(1);

    for(int i=0; i<Q; i++)
    {
        cin >> A >> B;

        int ans = 0;
        if(depth[A] < depth[B])
            swap(A ,B);
        for( ; depth[A] > depth[B]; A = par[A])
            ans = max(ans ,ed[A]);
        for( ; A != B; A = par[A] ,B = par[B])
            ans = max(ans ,max(ed[A] ,ed[B]));
        cout << ans << endl;
    }
}

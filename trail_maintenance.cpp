/**
we can solve the problem using kruskal's mst algorithm
but instead of sorting the edges every time we add new edge O(W*W*logwW + W^2)
we can add the new edge to a multiset in O(logW)
time complexity : O(WlogW + W^2)
*/

#include <bits/stdc++.h>
using namespace std;

#define MAX_N 202

int N ,W;
int A ,B ,C;

int par[MAX_N];
int Find(int U){
    return par[U] = (par[U] == U ? U : Find(par[U]));
}
bool Union(int U ,int V){
    U = Find(U) ,V = Find(V);
    if(U != V){
        par[U] = V;
        return 1;
    }
    return 0;
}

struct Edge{
    int fr ,to ,we;
    bool operator<(const Edge&rhs) const{
        return we < rhs.we;
    }
};
multiset <Edge> Edgs;

int main()
{
    scanf("%d%d",&N,&W);
    while(W--)
    {
        scanf("%d%d%d",&A,&B,&C);
        Edgs.insert({A-1 ,B-1 ,C});

        iota(par ,par+N ,0);
        int wes = 0 ,ins = 0;
        for(auto&ed : Edgs)
            if(Union(ed.fr ,ed.to))
                wes += ed.we ,ins++;

        printf("%d\n",(ins == N-1 ? wes : -1));
        fflush(stdout);
    }
}

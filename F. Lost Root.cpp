/**
observations : 
  1. longest path in tree = 2*depth-1 and it must contain the root node(lca(u ,v) = root node).
      and u ,v must be leaf nodes.
  2. we can check number of nodes between two nodes in n queries.

if we know u ,v such that path from u to v = 2*depth-1 then we can deduce the root node in (2*depth-1)^2 queries (depth <= 10)

probability of choosing two leaf nodes with the root node as their lca = ( (K*(K-1)/2) * (leaf_nodes_count/K)^2 ) / N^2
in worst case it will be as low as 0.06262 = 6.262%

probability of failing to get two nodes satisfying conditions 59 times = (1-0.06262)^59 = 0.02203 = 2.203%
so probability of succeeding = 1-0.02203 = 0.97797 = 97.797%
*/

#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rnd(int X){
    return uniform_int_distribution<int>(1,X)(rng);
}

int N ,K;

char s[5];
bool Ask(int A ,int B ,int C)
{
    if(B == A || B == C)
        return 1;
    printf("? %d %d %d\n",A,B,C);
    fflush(stdout);
    scanf("%s",s);
    return (s[0] == 'Y');
}

int main()
{
    scanf("%d%d",&N,&K);

    int depth = 1 ,nodes = 1 ,lvl = K;
    while(nodes+lvl <= N)
    {
        depth++;
        nodes += lvl;
        lvl *= K;
    }

    int U ,V;
    vector <int> ltol;
    while(true)
    {
        U = rnd(N) ,V = rnd(N);
        if(U == V)
            continue;

        vector <int> In;
        for(int i=1; i<=N; i++)
            if(Ask(U ,i ,V))
                In.push_back(i);

        if(In.size() == 2*depth-1)
        {
            ltol = In;
            break;
        }
    }

    for(int i : ltol)
    {
        int p1 = 0 ,p2 = 0;
        for(int j : ltol)
        {
            if(i == j)
                continue;

            if(Ask(U ,j ,i))
                p1++;
            else
                p2++;
        }

        if(p1 == p2)
        {
            printf("! %d\n",i);
            return 0;
        }
    }
}

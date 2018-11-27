/**
same editorial idea : https://codeforces.com/blog/entry/63461
*/

#include <bits/stdc++.h>
using namespace std;

#define pr(x) cout<<(x)<<'\n',0
#define sc(x) scanf("%d",&x);
#define scarr(x,a) for(int _=0;_<x;_++)scanf("%d",&a[_]);
#define prarr(x,a) for(int _=0;_<x;_++)printf("%d ",a[_]);
#define rep(_,x) for(int _=0;_<x;_++)
#define rep1(_,x) for(int _=1;_<=x;_++)

#define MAX_N 100005

int N;
int P;
vector<int> Adj[MAX_N];
int nodes[MAX_N];

int DFS(int Q)
{
    if(Adj[Q].empty()){
        nodes[1]++;
        return 1;
    }

    int lfs = 0;
    for(int u : Adj[Q])
        lfs += DFS(u);

    nodes[lfs]++;
    return lfs;
}

int main()
{
    sc(N)

    for(int i=2; i<=N; i++)
    {
        sc(P)
        Adj[P].push_back(i);
    }

    DFS(1);

    int happy = 0 ,ptr = 0;
    for(int i=1; i<=N; i++)
    {
        while(happy < i)
        {
            happy += nodes[ptr];
            ptr++;
        }

        printf("%d ",ptr-1);
    }
}

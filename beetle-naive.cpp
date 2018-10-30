/**
Naive approach : TLE(32/45)

we can simplify beetle move by knowing the range the beetle has
already visited so that we don't consider elements in this range
again in that way the beetle can only move to the first unvisited
cell from right and the last unvisited cell from left {L-1 ,R} or {L ,R+1}
,so the state of the beetle can be expressed by [L ,R ,P ,T]
where X[L] is leftmost position the beetle has already visited
and X[R] is rightmost position the beetle has already visited
and P is the current position of the beetle 0 = X[L] ,1 = X[R]
and T the current time.

the answer for the problem can be defined by function
f(L ,R ,P ,T) = max(M-T-abs(Pos-X[L-1]) + f(L-1 ,R ,0 ,P-X[L-1]+T)
                   ,M-T-abs(Pos-X[R+1]) + f(L ,R+1 ,1 ,X[R+1]-P+T))

we can apply dp to reach time complexity of O(2*N*N*logM)
*/

#include <bits/stdc++.h>
using namespace std;

#define MAX_N 305

int N ,M;
int X[MAX_N];

map <int ,int> dp[2][MAX_N][MAX_N];
int Solve(int L ,int R ,bool Pos ,int T)
{
    if(dp[Pos][L][R].find(T) != dp[Pos][L][R].end())
        return dp[Pos][L][R][T];

    int P = (Pos ? X[R] : X[L]);
    int &Ans = dp[Pos][L][R][T] = 0;

    if(L>0 && M > T+(P-X[L-1]))
        Ans = max(Ans ,M-T-(P-X[L-1]) + Solve(L-1 ,R ,0 ,(P-X[L-1])+T));
    if(R<N && M > T+(X[R+1]-P))
        Ans = max(Ans ,M-T-(X[R+1]-P) + Solve(L ,R+1 ,1 ,(X[R+1]-P)+T));

    return Ans;
}

int main()
{
    scanf("%d%d",&N,&M);
    for(int i=0; i<N; i++)
        scanf("%d",&X[i]);

    X[N] = 0; sort(X ,X+N+1);

    int zero = lower_bound(X ,X+N+1 ,0)-X;
    printf("%d\n",Solve(zero ,zero ,0 ,0));
}

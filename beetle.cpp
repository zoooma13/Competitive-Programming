/**
we can modify the naive approach by modifying our solve function
instead of calculating the best answer from given position let's calculate
the min time that the beetle can visit R drops of water starting
from X=0 in that time then ans will be equal
max(R*M - Solve(x0 ,x0 ,0 ,R)) for all R = {1..N}

Time complexity for solve function : O(2*N*N) = O(N^2)
Total time complexity : O(2*N*N*N) = O(N^3)

naive approach : https://github.com/zoooma13/Competitive-Programming/blob/master/beetle-naive.cpp
*/
#include <bits/stdc++.h>
using namespace std;

#define MAX_N 305

int N ,M;
int X[MAX_N];

int dp[2][MAX_N][MAX_N];
int Solve(int L ,int R ,bool Pos ,int Rem)
{
    if(Rem == 0)
        return 0;
    if(~dp[Pos][L][R])
        return dp[Pos][L][R];

    int P = (Pos ? X[R] : X[L]);
    int &Ans = dp[Pos][L][R] = 1e9;

    if(L>0) Ans = min(Ans ,(P-X[L-1])*Rem + Solve(L-1 ,R ,0 ,Rem-1));
    if(R<N) Ans = min(Ans ,(X[R+1]-P)*Rem + Solve(L ,R+1 ,1 ,Rem-1));

    return Ans;
}

int main()
{
    scanf("%d%d",&N,&M);
    for(int i=0; i<N; i++)
        scanf("%d",&X[i]);

    X[N] = 0; sort(X ,X+N+1);
    int zero = lower_bound(X ,X+N+1 ,0)-X ,Ans = 0;

    for(int i=1; i<=N; i++)
    {
        memset(dp ,-1 ,sizeof dp);
        Ans = max(Ans ,i*M - Solve(zero ,zero ,0 ,i));
    }

    printf("%d\n",Ans);
}

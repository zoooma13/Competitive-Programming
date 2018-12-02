/**
same editorial idea : https://codeforces.com/blog/entry/63544
*/

#include <bits/stdc++.h>
using namespace std;

#define MAX_N 500005

int N ,C;
int A[MAX_N];

set <int> nums;
vector <int> idx[MAX_N];
int eqc[MAX_N];

int main()
{
    scanf("%d%d",&N,&C);
    for(int i=0; i<N; i++)
    {
        scanf("%d",&A[i]);

        nums.insert(A[i]);
        idx[A[i]].push_back(i);
        eqc[i+1] = eqc[i] + (A[i] == C);
    }

    int Ans = 0;
    for(int x : nums)
    {
        if(x == C)
            continue;

        int best = 0 ,curr = 0;
        for(int i=1; i<idx[x].size(); i++)
        {
            curr = max(curr ,0);
            curr += -(eqc[idx[x][i]+1]-eqc[idx[x][i-1]]) + 1;
            best = max(best ,curr);
        }

        Ans = max(Ans ,best+1);
    }

    printf("%d\n",Ans+eqc[N]);
}

/**
we can reduce the answer by removing cell that appears
the most in the submatrices consisting of ones.
ans = number of submatrices consisting of ones - the most frequent cell.

time complexity : O(N^3)
*/

#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>
using namespace std;

#define MAX_N 755

int N ,M;
string G;
bool S[MAX_N][MAX_N];

short ntv[MAX_N][MAX_N];
int trck[MAX_N][MAX_N];
long long up[MAX_N][MAX_N];

int main()
{
    cin >> N >> M;
    for(int i=0; i<N; i++)
    {
        cin >> G;
        for(int j=0; j<M; j++)
            S[i][j] = G[j]-'0';
    }

    long long ans = 0;
    for(int i=0; i<N; i++)
    for(int j=0; j<M; j++)
    {
        for(int l=j; l<M; l++)
        {
            if(!S[i][l])
            {
                fill(ntv[j]+l ,ntv[j]+M+1 ,i+1);
                break;
            }

            ans += (i-ntv[j][l]+1);

            trck[ntv[j][l]][j] += 1;
            trck[i+1][j] += -1;
            up[i+1][j] += -(i-ntv[j][l]+1);

            trck[ntv[j][l]][l+1] += -1;
            trck[i+1][l+1] += 1;
            up[i+1][l+1] += (i-ntv[j][l]+1);
        }
    }

    long long b = 0 ,h = 0;
    for(int j=0; j<M; j++ ,b=0 ,h=0)
    for(int i=0; i<N; i++)
    {
        h += trck[i][j];
        b += up[i][j] + h;
        up[i][j] = b;
    }

    long long mx = 0;
    for(int i=0; i<N; i++ ,b=0)
    for(int j=0; j<M; j++)
        mx = max(mx ,b += up[i][j]);

    cout << ans-mx << endl;
}

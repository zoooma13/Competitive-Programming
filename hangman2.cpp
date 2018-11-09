/**
since NK < 3*10^4 we can solve the problem by two ways

if N <= 200 ,K > 150
  check for every string if there is other strings satisfying the conditions
  complexity O(N*N*K)
if N > 200 ,K <= 150
    since two strings can only differ in two characters to satisfy the conditions
    we can remove two characters at positions j,l from all the strings and check if
    two strings are equal we can do so by using polynomial hashing and unordered_map
    complexity O(N*K*K)
*/

#include <bits/stdc++.h>
using namespace std;

#define MAX_N 30004

typedef unsigned long long ull;

int base = 1e9+7;
vector <ull> pow2{1};

int T;
int N ,K;
ull hsh[MAX_N];
bool ans[MAX_N];

int main()
{
    while(pow2.size() <= MAX_N)
        pow2.push_back(pow2.back()*base);

    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&N,&K);
        char S[N+1][K+1];
        memset(ans ,0 ,sizeof ans);
        memset(S ,0 ,sizeof S);

        for(int i=0; i<N; i++)
        {
            ull hash2 = 0;
            for(int j=0; j<K; j++)
            {
                do{
                    S[i][j] = getchar();
                }while(!('a' <= S[i][j] && S[i][j] <= 'z'));
                hash2 += S[i][j]*pow2[j];
            }
            hsh[i] = hash2;
        }

        if(N <= 200)
        {
            for(int i=0; i<N; i++)
            for(int j=0; j<N; j++) if(i != j)
            {
                int diff = 0;
                for(int l=0; l<K; l++)
                    diff += (S[i][l] != S[j][l]);
                if(diff <= 2){
                    ans[i] = 1;
                    break;
                }
            }
        }
        else
        {
            unordered_map <ull ,int> bef;
            for(int j=0; j<K; j++)
            for(int l=j+1; l<K; l++)
            {
                bef.clear();
                for(int i=0; i<N; i++)
                {
                    int&ss = bef[hsh[i] - S[i][j]*pow2[j] - S[i][l]*pow2[l]];
                    if(ss)
                        ans[i] = ans[ss-1] = 1;
                    ss = i+1;
                }
            }
        }

        for(int i=0; i<N; i++)
            putchar(ans[i] + '0');
        putchar('\n');
    }
}

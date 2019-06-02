/**
a naive solution would be for each element flip every possible 4 bits and check if there exists an element
with that value this solution works in N*(20C4) which is not fast enough to pass.

lets create a dp[d][m] that stores the number of elements from the array that we can modify their value by flipping exactly d bits to be equal to m.
instead of flipping 4 bits for each element we can divide a number c into 2 halves a = (n>>10) and b = n&((1<<10)-1) so that c = (a*2^10)+b 
now flip at most 4 bits in a and increase dp[d][m_a*2^10+b] by 1 where m_a is the modified a and d is # of diff bits between a and m_a
then for the second half flip at most 4 bits and add dp[4-d][a*2^10+m_b] where m_b is modified b and d is # of diff bits between b and m_b
this will be equivalent to flipping all 4 bits for each element.

time complexity : O(N*2^10)

because of tight tl we will have to do loop unrolling manually or by using pragma.
since the 2 inner loops are really simple they can be unrolled and would save processing time.
*/

#pragma GCC optimize ("unroll-loops")

#include <bits/stdc++.h>
using namespace std;

#define MAX_N 100005

int n;
int a[MAX_N];
int dp[5][1024*1024];

int main()
{
    freopen("aiacubiti.in" ,"r" ,stdin);
    freopen("aiacubiti.out" ,"w" ,stdout);

    int popcount[1024];
    for(int b=0; b<1024; b++)
        popcount[b] = __builtin_popcount(b);

    scanf("%d",&n);
    for(int i=0; i<n; i++)
        scanf("%d",&a[i]);

    long long ans = 0;
    for(int i=0; i<n; i++)
    {
        int fh = (a[i]>>10) ,sh = (a[i]&1023);
        for(int d ,b=0; b<1024; b++){
            d = popcount[b^sh];
            if(d <= 4)
                ans += dp[4-d][(fh<<10)|b];
        }
        for(int d ,b=0; b<1024; b++){
            d = popcount[b^fh];
            if(d <= 4)
                dp[d][(b<<10)|sh]++;
        }
    }

    printf("%lld\n",ans);
}


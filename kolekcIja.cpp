/**
problem description :
 given m points on the x-axis.
 what is the minimum number of points covered such that you can only cover segments of length k and the points covered contains all the m points.

we can sort the points and do dp using the following recurrence :
 (i:1->m)dp[i] = MIN(j:1->i){ MAX(k ,a[i]-a[j]+1)+dp[j-1] }
where dp[i] represents the min number of necessary points to be covered to contain the first i points.
it can be easily computed in O(m^2) but this complexity is not efficient enough.

let's divide points before point i into 2 types:
 1. points with distance less than or equal to k ,in this case we don't care about the actual value of their position.
    let such point index be j then we can substitute the MAX part in the recurrence with k+dp[j-1].
 2. points with distance more than k ,let such point index be j we can substitute the MAX part with (a[i]) + (-a[j]+1+dp[j-1]).

if we traverse points by their ascending order a point will first be of type 1 and after some time it will change to type 2 and remain type 2 to the end.
so we can keep track of both types of points and compute their contribution using the method mentioned above.
since the dp values are monotonic we can keep track of one point of each type that minimizes the contribution.

tags : two pointers ,dp ,line sweep
time complexity : O(m + m*logm)

another approach : https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/COCI/official/2008/olympiad_solutions/solutions.pdf
*/

#include <bits/stdc++.h>
using namespace std;

#define MAX_M 300005

int k ,n;
int m;
int a[MAX_M] ,b[MAX_M];

int main()
{
    scanf("%d%d",&n,&k);
    scanf("%d",&m);
    for(int i=1; i<=m; i++)
        scanf("%d",&a[i]) ,b[i] = a[i];

    sort(a+1 ,a+m+1);

    vector <pair<int ,int>> dp(m+1);
    pair <int ,int> mi_dp = {1e9 ,1e9};
    int kdiff_ptr = 1;
    for(int i=1; i<=m; i++){
        while(kdiff_ptr < i && a[i]-a[kdiff_ptr]+1>k){
            mi_dp = min(mi_dp ,{-a[kdiff_ptr]+dp[kdiff_ptr-1].first ,kdiff_ptr-1});
            kdiff_ptr++;
        }

        dp[i] = min(make_pair(k+dp[kdiff_ptr-1].first ,kdiff_ptr-1)
                   ,make_pair(a[i]+mi_dp.first+1 ,mi_dp.second));
    }

    printf("%d\n",dp[m].first);

    vector <pair<int ,int>> segments;
    for(int i=m; i; i=dp[i].second){
        int fr = a[dp[i].second+1] ,to = a[i];
        while(fr <= to){
            if(fr+k-1 <= to)
                segments.push_back({fr ,fr+k-1});
            else
                segments.push_back({to-k+1 ,to});
            fr += k;
        }
    }
    sort(segments.begin() ,segments.end());

    for(int i=1; i<=m; i++){
        auto&ans = *prev(upper_bound(segments.begin() ,segments.end() ,make_pair(b[i] ,INT_MAX)));
        printf("%d %d\n",ans.first,ans.second);
    }
}

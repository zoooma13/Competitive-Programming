/**
https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/COCI/official/2008/contest6_solutions/solutions.pdf
*/

#include <bits/stdc++.h>
using namespace std;

#define MAX_N 100005
#define INF 0x3f3f3f3f3f3f3f3f

int n;
int a[MAX_N] ,b[MAX_N];

int main()
{
    scanf("%d",&n);
    for(int i=1; i<=n; i++)
        scanf("%d%d",&a[i],&b[i]);

    sort(a+1 ,a+n+1);
    sort(b+1 ,b+n+1);

    vector <vector<int>> perm{{0},{0,1},{1,0}};
    vector <int> p = {0 ,1 ,2};
    do{perm.push_back(p);}
    while(next_permutation(p.begin() ,p.end()));

    vector <long long> dp(n+1 ,INF); dp[0] = 0LL;
    for(int i=1; i<=n; i++){
        for(auto&p : perm){
            if(i < p.size())
                continue;

            bool bad = false;
            int curr = 0;
            for(int j=0; j<p.size(); j++){
                if(a[i-j] == b[i-p[j]])
                    bad = true;
                curr += abs(a[i-j] - b[i-p[j]]);
            }

            if(!bad)
                dp[i] = min(dp[i] ,dp[i-p.size()]+curr);
        }
    }

    printf("%lld\n",dp[n]);
}

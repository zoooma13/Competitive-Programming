/**
http://usaco.org/current/data/sol_movie_gold.html
*/

#include <bits/stdc++.h>
using namespace std;

#define MAX_N 20

int n ,l;
int d[MAX_N] ,c[MAX_N];
vector <int> st[MAX_N];

int dp[1<<MAX_N];

int main()
{
    freopen("movie.in" ,"r" ,stdin);
    freopen("movie.out" ,"w" ,stdout);

    scanf("%d%d",&n,&l);
    for(int i=0; i<n; i++){
        scanf("%d%d",&d[i],&c[i]); st[i].resize(c[i]);
        for(int&t : st[i])
            scanf("%d",&t);
    }

    int ans = 1e9;
    for(int i=0; i<(1<<n); i++){
        int curr_tm = dp[i];
        if(curr_tm >= l)
            ans = min(ans ,__builtin_popcount(i));
        //cout << i << " = " << curr_tm << endl;
        for(int b=0; b<n; b++)
            if(!(i&(1<<b))){
                auto it = upper_bound(st[b].begin() ,st[b].end() ,curr_tm);
                if(it == st[b].begin())
                    continue;
                int lst_tm = *prev(it);
                dp[i|(1<<b)] = max(dp[i|(1<<b)] ,max(curr_tm ,lst_tm+d[b]));
        }
    }

    printf("%d\n",ans == 1e9 ? -1 : ans);
}

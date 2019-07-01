/**
http://usaco.org/current/data/sol_guard_gold.html
*/

#include <bits/stdc++.h>
using namespace std;

int n ,H;
int w[20] ,s[20] ,h[20];

bool cmp(int i,int j){
    return s[i]-w[j] < s[j]-w[i];
}

int main()
{
    freopen("guard.in" ,"r" ,stdin);
    freopen("guard.out" ,"w" ,stdout);

    scanf("%d%d",&n,&H);
    for(int i=0; i<n; i++)
        scanf("%d%d%d",&h[i],&w[i],&s[i]);

    long long ans = -1;
    for(int b=1; b<(1<<n); b++)
    {
        long long hyts = 0;
        vector <int> cows;
        for(int i=b; i; i-=(i&-i)){
            cows.push_back(log2(i&-i));
            hyts += h[cows.back()];
        }

        if(hyts >= H){
            sort(cows.begin() ,cows.end() ,cmp);

            long long st = INT_MAX ,we = 0;
            for(int&c : cows){
                st = min(st ,s[c]-we);
                we += w[c];
            }

            ans = max(ans ,st);
        }
    }

    if(~ans)
        printf("%lld\n",ans);
    else
        printf("Mark is too tall\n");
}

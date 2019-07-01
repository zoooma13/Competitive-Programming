/**
http://usaco.org/current/data/sol_cowjog_gold.html
*/

#include <bits/stdc++.h>
using namespace std;

int n ,t;
int p ,s;

int main()
{
    freopen("cowjog.in" ,"r" ,stdin);
    freopen("cowjog.out" ,"w" ,stdout);

    multiset <long long> lanes;
    scanf("%d%d",&n,&t);
    for(int i=0; i<n; i++){
        scanf("%d%d",&p,&s);
        long long curr = 1LL*t*s+p;
        auto it = lanes.lower_bound(curr);
        if(it == lanes.begin())
            lanes.insert(curr);
        else{
            lanes.erase(prev(it));
            lanes.insert(curr);
        }
    }

    printf("%d\n",lanes.size());
}

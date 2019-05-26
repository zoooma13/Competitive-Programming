/**
let b = 0
starting from the most significant bit i and decreasing :
 if we can get a solution without using any elements that contains b|(1<<i) bits add i to b (b |= (1<<i))
the answer is the bitwise inverse of b
we can check if a solution without b exists by applying knapsack
because of strict TL we have to optimize the knapsack by :
 -using bitset
 -replacing repeated number a by 1*a ,2*a ,3*a ,4*a ...
  so we can get all its possible sums in knapsack
*/

#include <bits/stdc++.h>
using namespace std;

#define MAX_N 100005
#define MAX_S 50004

int n ,s;
pair<int ,int> a[MAX_N];

bool can(int bits){
    bitset <MAX_S> bs; bs[0] = 1;
    for(int i=0; i<n; i++)
        if((a[i].second&bits) == 0){
            bs |= (bs<<a[i].first);
            if(bs[s])
                return 1;
        }
    return 0;
}
int main()
{
    freopen("sormin.in" ,"r" ,stdin);
    freopen("sormin.out" ,"w" ,stdout);

    scanf("%d%d",&n,&s);
    for(int i=0; i<n; i++)
        scanf("%d",&a[i].first);
    sort(a ,a+n);

    int idx = 0;
    for(int cnt=0 ,i=0; i<n; i++){
        cnt++;
        if(a[i].first == a[i+1].first)
            continue;
        while(cnt){
            int p = 1;
            while(cnt >= p){
                a[idx++] = {a[i].first*p ,a[i].first};
                cnt -= p;
                p *= 2;
            }
        }
    } n = idx;

    int without = 0;
    for(int i=12; ~i; i--)
        if(can(without|(1<<i)))
            without |= (1<<i);

    vector <pair<int ,int>> from(s+1 ,{-1 ,-1}); from[0] = {0 ,0};
    for(int i=0; i<n; i++){
        if(a[i].second&without)
            continue;
        int val = a[i].first;
        for(int j=s; j>=val; j--)
            if(~from[j-val].first && !~from[j].first)
                from[j] = a[i];
    }

    vector <int> ans;
    while(s){
        int cnt = from[s].first/from[s].second;
        for(int i=0; i<cnt; i++)
            ans.push_back(from[s].second);
        s -= from[s].first;
    }

    printf("%d %d\n",(((1<<13)-1)^without),ans.size());
    for(int i : ans)
        printf("%d ",i);
    printf("\n");
}

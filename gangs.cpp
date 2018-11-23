/**
same sol idea :
https://github.com/updown2/OI-Practice/blob/master/USACO/2012-2013/December/Gold/Gangs.cpp
*/

#include <bits/stdc++.h>
using namespace std;

#define MAX_N 102
#define pii pair<int ,int>
#define fi first
#define se second

int N ,M;
int C[MAX_N];

void next_state(int&cow ,int&cnt ,int new_cow){
    if(cnt == 0)
        cow = new_cow;
    cnt += (cow == new_cow ? 1 : -1);
}

int max_cows(int cow ,int cnt){
    priority_queue <pii> pq;
    for(int i=1; i<M; i++)
        if(C[i] > 0)
            pq.push({C[i] ,i});

    while(!pq.empty())
    {
        pii t = pq.top(); pq.pop();
        next_state(cow ,cnt ,t.se);
        if(t.fi > 1)
            pq.push({t.fi-1 ,t.se});
    }

    return C[0] + (cow == 0 ? cnt : -cnt);
}

int main()
{
    freopen("gangs.in" ,"r" ,stdin);
    freopen("gangs.out" ,"w" ,stdout);

    scanf("%d%d",&N,&M);
    for(int i=0; i<M; i++)
        scanf("%d",&C[i]);

    int best = max_cows(0 ,0);
    if(best <= 0){
        printf("NO\n");
        return 0;
    }

    printf("YES\n");
    printf("%d\n",best);

    int curr_cow = 0 ,cow_cnt = 0;
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<M; j++)
        {
            if(C[j] == 0)
                continue;

            int  bcc = curr_cow ,bcn = cow_cnt;
            next_state(curr_cow ,cow_cnt ,j);
            C[j]--;

            if(max_cows(curr_cow ,cow_cnt) == best){
                printf("%d\n",j+1);
                break;
            }

            curr_cow = bcc ,cow_cnt = bcn;
            C[j]++;
        }
    }
}

/**
same sol idea : https://github.com/nikolapesic2802/Programming-Practice/blob/master/Long%20Mansion/main.cpp
*/

#include <bits/stdc++.h>
using namespace std;

#define MAX_N 500005

int N;
int C[MAX_N];
int B ,K;
vector <int> Keys[MAX_N];
int Q;
int X ,Y;

int last[MAX_N];
int nl[MAX_N] ,nr[MAX_N];
int st[MAX_N] ,en[MAX_N];

int main()
{
    scanf("%d",&N);
    for(int i=0; i<N-1; i++)
        scanf("%d",&C[i]);
    for(int i=0; i<N; i++)
    {
        scanf("%d",&B);
        while(B--){
            scanf("%d",&K);
            Keys[i].push_back(K);
        }
    }

    memset(last ,-1 ,sizeof last);
    for(int i=0; i<N-1; i++){
        for(int j : Keys[i])
            last[j] = i;
        nl[i] = last[C[i]];
    }
    memset(last ,-1 ,sizeof last);
    for(int i=N-2; ~i; i--){
        for(int j : Keys[i+1])
            last[j] = i+1;
        nr[i] = last[C[i]];
    }

    auto can_left = [&](int i){
        return (st[i] > 0 && ~nr[st[i]-1] && nr[st[i]-1] <= en[i]);
    };
    auto can_right = [&](int i){
        return (en[i] < N-1 && ~nl[en[i]] && st[i] <= nl[en[i]]);
    };

    for(int i=0; i<N; i++)
    {
        st[i] = en[i] = i;
        while(true)
        {
            if(can_left(i)){
                en[i] = max(en[i] ,en[st[i]-1]);
                st[i] = st[st[i]-1];
            }
            else if(can_right(i))
                en[i]++;
            else
                break;
        }
    }

    scanf("%d",&Q);
    while(Q--)
    {
        scanf("%d%d",&X,&Y); X-- ,Y--;
        printf(st[X]<=Y&&Y<=en[X] ? "YES\n" : "NO\n");
    }
}

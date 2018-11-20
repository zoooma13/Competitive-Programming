#include <bits/stdc++.h>
//#include "grader.cpp"

#define MAX_S 100005
#define MAX_P 50005
#define MAX_Si 105
#define MAX_PREF 1005

int S ,P;
int s[MAX_S];
int p[MAX_P];
int first[MAX_Si][MAX_S];

int op = 0;
int pref[MAX_Si];
int dp[MAX_S][MAX_PREF];

int Solve(int i ,int pt)
{
    if(pt == P)
        return S-i;
    if(first[p[pt]][i+1] == -1)
        return 0;

    if(++op < 1e7){ //check dp for current state and add its ans if it is a new state
        int&ret = dp[i][pref[s[i]]];
        if(ret)
            return ret;

        pref[p[pt]]++;
        ret = Solve(first[p[pt]][i+1] ,pt+1);
        pref[p[pt]]--;
        return ret;
    }
    else //just compute the answer for this state
        return Solve(first[p[pt]][i+1] ,pt+1);
}

long long conta(int _S, int _s[], int _P, int _p[]) {
    S = _S ,P = _P;
    for(int i=0; i<_S; i++) s[i] = _s[i];
    for(int i=0; i<_P; i++) p[i] = _p[i];

    memset(first ,-1 ,sizeof first);
    for(int i=S-1; ~i; i--)
    {
        for(int j=0; j<=100; j++)
            first[j][i] = first[j][i+1];
        first[s[i]][i] = i;
    }

    pref[p[0]] = 1;
    long long Ans = 0LL;
    for(int i=0; i<=S-P; i++)
    {
        int x = 0;
        if(~first[p[0]][i])
            x = Solve(first[p[0]][i] ,1);
        if(!x)
            break;
        Ans += x;
    }
    return Ans;
}

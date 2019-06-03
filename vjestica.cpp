/**
same as editorial : https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/COCI/official/2017/contest1_solutions/solutions.pdf
time complexity : O(3^n)
*/

#include <bits/stdc++.h>
using namespace std;

int lg2[1<<16];

int n;
string s;
vector <int> ch_cnt[16];

int dp[1<<16];
int solve(int bts){
    if((bts&(bts-1)) == 0){
        int idx = lg2[bts&-bts] ,ret = 0;
        for(int c=0; c<26; c++)
            ret += ch_cnt[idx][c];
        return ret;
    }
    if(~dp[bts])
        return dp[bts];

    vector <int> mi(26 ,INT_MAX);
    for(int b=bts; b; b-=(b&-b)){
        int idx = lg2[b&-b];
        for(int c=0; c<26; c++)
            mi[c] = min(mi[c] ,ch_cnt[idx][c]);
    }
    int all_mi = 0;
    for(int c=0; c<26; c++)
        all_mi += mi[c];

    int ans = INT_MAX;
    for(int b=bts; b; b=(b-1)&bts){
        if(b && (bts^b))
            ans = min(ans ,solve(b)+solve(bts^b));
    }

    return dp[bts] = ans-all_mi;
}

int main()
{
    lg2[0] = -1;
    for(int i=1; i<(1<<16); i++){
        lg2[i] = lg2[i-1];
        if((i&(i-1)) == 0)
            lg2[i]++;
    }

    cin >> n;
    for(int i=0; i<n; i++){
        ch_cnt[i].resize(26);
        cin >> s;
        for(char c='a'; c<='z'; c++)
            ch_cnt[i][c-'a'] = count(s.begin() ,s.end() ,c);
    }

    memset(dp ,-1 ,sizeof dp);
    cout << solve((1<<n)-1)+1 << endl;
}

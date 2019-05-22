/**
same editorial's idea : https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/Baltic/official/boi2006_solutions
*/

#include <bits/stdc++.h>
using namespace std;

#define MAX_M 2000006

int n ,m;
int seq[MAX_M];
vector <pair<int ,long long>> blcks;

void decode(){
    for(int e=0 ,i=0; i<m; ){
        if(seq[i] != e){
            if(!blcks.empty() && blcks.back().first == seq[i])
                    blcks.back().second += 1;
            else
                blcks.push_back({seq[i] ,1});
            i++;
        }
        else{
            if(seq[i+1] == e){
                if(!blcks.empty() && blcks.back().first == e)
                    blcks.back().second += seq[i+2]+1;
                else
                    blcks.push_back({e ,seq[i+2]+1});
            }
            else if(seq[i+2] == 0)
                e = seq[i+1];
            else{
                if(!blcks.empty() && blcks.back().first == seq[i+1])
                    blcks.back().second += seq[i+2]+3;
                else
                    blcks.push_back({seq[i+1] ,seq[i+2]+3});
            }
            i += 3;
        }
    }
}
int calc0(long long x){
    return 3*(x/(n+2)) + min(3LL ,x%(n+2));
}
int calc1(long long x){
    return 3*(x/(n)) + 3*(bool)(x%(n));
}
///calc0 <= calc1

int ans[MAX_M+1] ,ans_idx = MAX_M;
void get0(long long x ,int e ,int b){
    for( ; n+2<=x; x-=n+2){
        ans[ans_idx--] = n-1;
        ans[ans_idx--] = b;
        ans[ans_idx--] = e;
    }
    if(x > 3){
        ans[ans_idx--] = x-3;
        ans[ans_idx--] = b;
        ans[ans_idx--] = e;
    }else{
        while(x--)
            ans[ans_idx--] = b;
    }
}
void get1(long long x ,int e){
    for( ; n<=x; x-=n){
        ans[ans_idx--] = n-1;
        ans[ans_idx--] = e;
        ans[ans_idx--] = e;
    }
    if(x > 0){
        ans[ans_idx--] = x-1;
        ans[ans_idx--] = e;
        ans[ans_idx--] = e;
    }
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0; i<m; i++)
        scanf("%d",&seq[i]);

    decode();
    int k = blcks.size();

    vector <int> dp(n ,3); dp[0] = 0;
    set <pair<int ,int>> ss;
    for(int i=0; i<n; i++)
        ss.insert({dp[i] ,i});

    int idx = 0;
    vector <int> ch(k);
    for(auto b : blcks){
        int c0 = calc0(b.second) ,c1 = calc1(b.second);

        ss.erase({dp[b.first] ,b.first});
        dp[b.first] = dp[b.first]+c1 ,ch[idx] = b.first;

        auto mi = *ss.begin();
        if(dp[b.first] > mi.first+c0+3)
            dp[b.first] = mi.first+c0+3 ,ch[idx] = mi.second;

        dp[b.first] -= c0;
        ss.insert({dp[b.first] ,b.first});
        idx++;
    }

    ans_idx = MAX_M;
    int e = ss.begin()->second;
    for(int i=k-1; ~i; i--){
        if(blcks[i].first == e){
            if(e == ch[i]){
                get1(blcks[i].second ,e);
            }else{
                ans[ans_idx--] = 0;
                ans[ans_idx--] = e;
                ans[ans_idx--] = ch[i];
                get0(blcks[i].second ,ch[i] ,blcks[i].first);
                e = ch[i];
            }
        }
        else{
            get0(blcks[i].second ,e ,blcks[i].first);
        }
    }

    if(e){
        ans[ans_idx--] = 0;
        ans[ans_idx--] = e;
        ans[ans_idx--] = 0;
    }

    printf("%d\n",MAX_M-ans_idx);
    for(int i=ans_idx+1; i<=MAX_M; i++)
        printf("%d ",ans[i]);
    printf("\n");
}

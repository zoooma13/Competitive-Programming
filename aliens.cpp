/**
https://ioinformatics.org/files/ioi2016solutions.pdf
*/

#include <bits/stdc++.h>
using namespace std;

#define MAX_N 100005
#define L first
#define R second
#define sqr(x) 1LL*(x)*(x)

struct line{
    long long m, c;
    int cnt;
    pair<long long ,int> eva(long long x) { return {m * x + c ,cnt}; }
    long double intersectX(line l) { return (long double) (c - l.c) / (l.m - m); }
};

struct hull:deque<line>{
    void add(long long m ,long long b ,int cnt){
        line cur = {m ,b ,cnt};
        while (size() >= 2 && cur.intersectX(front()) <= front().intersectX(at(1)))
            pop_front();
        push_front(cur);
    }
    pair<long long ,int> eval(long long x){
        while(size() >= 2 && back().eva(x) >= at(size()-2).eva(x))
            pop_back();
        return back().eva(x);
    }
};

int n ,m ,K;
vector <pair<int ,int>> rngs;

pair<long long ,int> solve(long long C){
    hull h;
    vector <pair<long long ,int>> dp(n+1);
    for(int i=1; i<=n; i++){
        long long miB = sqr(rngs[i].L-1) +dp[i-1].first -sqr(max(rngs[i-1].R-rngs[i].L+1 ,0)) + C;
        h.add(-2*(rngs[i].L-1) ,+miB ,dp[i-1].second);
        auto bst = h.eval(rngs[i].R);
        dp[i] = {sqr(rngs[i].R) + bst.first ,bst.second+1};
    }
    return dp[n];
}

int main()
{
    scanf("%d%d%d",&n,&m,&K); assert(n < MAX_N);
    for(int x ,y ,i=0; i<n; i++){
        scanf("%d%d",&y,&x);
        if(x > y) swap(x ,y);
        rngs.push_back({x ,y});
    }

    ///Building good ranges
    rngs.push_back({-1 ,-1});
    sort(rngs.begin() ,rngs.end() ,[](pair<int ,int>&i ,pair<int ,int>&j){
        return (i.R == j.R) ? i.L > j.L : i.R < j.R;
    });
    vector <pair<int ,int>> good;
    for(int miL=2e9 ,i=n; ~i; i--)
        if(rngs[i].L < miL){
            good.push_back(rngs[i]);
            miL = rngs[i].L;
        }
    reverse(good.begin() ,good.end());
    swap(rngs ,good);
    n = rngs.size()-1 ,K = min(K ,n);
    ///END

    long long st = 0 ,en = sqr(m) ,mid;
    while(st <= en){
        mid = (st+en)>>1;
        auto curr = solve(mid);
        if(curr.second <= K)
            en = mid-1;
        else
            st = mid+1;
    }

    printf("%lld\n",solve(en+1).first-K*(en+1));

}

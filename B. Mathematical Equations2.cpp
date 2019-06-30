#include <bits/stdc++.h>
using namespace std;
 
#define MAX_N 10005
 
const long long MOD = 1e9+7LL;
long long GM(long long Num){
    return ((Num%MOD)+MOD)%MOD;
}
 
bool query = 0;
 
struct line{
    long long m ,b;
    mutable function <const line*()> succ;
    bool operator<(const line rhs) const
    {
        if(!query)
            return m < rhs.m;
 
        const line *s = succ();
        return s ? (b-s->b) < (rhs.m*(s->m-m)) : 0;
    }
};
 
struct hull:multiset<line>{
    bool bad(iterator y)
    {
        auto z = next(y);
        if(y == begin())
        {
            if(z == end())
                return 0;
            return (y->m==z->m) && (y->m<=z->m);
        }
 
        auto x = prev(y);
        if(z == end())
            return (y->m==x->m) && (y->m<=x->m);
 
        return (1.0)*(x->b-y->b)*(z->m-y->m) >= (1.0)*(y->b-z->b)*(y->m-x->m);
    }
    void add(long long m ,long long b)
    {
        auto it = insert({m,b});
        it->succ = [=]{ return next(it)==end() ? 0 : &*next(it); };
 
        if(bad(it))
        {
            erase(it);
            return;
        }
 
        while(next(it) != end() && bad(next(it))) erase(next(it));
        while(it != begin()     && bad(prev(it))) erase(prev(it));
    }
    long long eval(long long x)
    {
        query = 1;
        auto l = lower_bound({x,0});
        query = 0;
        return l->m*x+l->b;
    }
};
 
hull h[105];
 
int T;
int N ,SQ = 100;
int A[MAX_N];
int R[MAX_N];
 
long long SA[MAX_N];
long long SAi[MAX_N];
 
long long F(int j ,int i){
    return (-j+1LL)*SA[i] - (-j+1LL)*SA[j-1] +SAi[i] -SAi[j-1];
}
 
long long Query(int st ,int en)
{
    long long Ret = -9e18;
    for( ; ((st-1)/SQ)==(st/SQ) && st <= en; st++)
        Ret = max(Ret ,F(st ,en));
    for( ; st+SQ <= en; st += SQ)
        Ret = max(Ret ,h[st/SQ].eval(SA[en])+SAi[en]);
    for( ; st <= en; st++)
        Ret = max(Ret ,F(st ,en));
    return Ret;
}
 
long long Solve()
{
    for(int i=1; i<=N; i++)
        h[i/SQ].clear();
    for(int i=1; i<=N; i++)
    {
        SA[i] = SA[i-1]+A[i];
        SAi[i] = SAi[i-1]+(i*1LL*A[i]);
        h[i/SQ].add(-i+1 ,-((-i+1)*SA[i-1])-SAi[i-1]);
    }
 
    long long Ans = 0LL;
    for(int i=1; i<=N; i++)
        Ans += Query(i-R[i]+1 ,i);
 
    return GM(Ans);
}
 
int main()
{
    scanf("%d",&T);
 
    while(T--)
    {
        scanf("%d",&N);
        for(int i=1; i<=N; i++)
            scanf("%d",&A[i]);
        for(int i=1; i<=N; i++)
            scanf("%d",&R[i]);
 
        printf("%I64d\n",Solve());
    }
}

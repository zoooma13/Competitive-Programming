#include <bits/stdc++.h>
using namespace std;
 
#define MAX_N 10005
#define FL(P) (P<<1)+1
#define FR(P) (P<<1)+2
 
const long long MOD = 1e9+7LL;
long long GM(long long Num){
    return ((Num%MOD)+MOD)%MOD;
}
 
bool query = 0;
 
struct line{
    long long m ,b;
    mutable function<const line*()> succ;
    bool operator<(const line rhs)const
    {
        if(!query)
            return (m < rhs.m);
 
        const line* s = succ();
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
            return (y->m == z->m) && (y->b <= z->b);
        }
 
        auto x = prev(y);
        if(z == end())
            return (y->m == x->m) && (y->b <= x->b);
 
        return (1.0)*(x->b - y->b)*(z->m - y->m) >= (1.0)*(y->b - z->b)*(y->m - x->m);
    }
    void add(long long m ,long long b)
    {
        auto it = insert({m,b});
        it -> succ = [=]{ return (next(it)==end())?0:&*next(it); };
 
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
        line l = *lower_bound({x,0});
        query = 0;
        return (l.m*x+l.b);
    }
};
 
hull h[4*MAX_N];
 
int T;
int N;
int A[MAX_N];
int R[MAX_N];
 
long long SumA[MAX_N];
long long SumAi[MAX_N];
 
int SQ;
 
void Merge(int P ,int LP ,int RP)
{
    h[P].clear();
    for(line l : h[LP])
        h[P].add(l.m ,l.b);
    for(line l : h[RP])
        h[P].add(l.m ,l.b);
}
 
void Build(int L=1 ,int R=N ,int P=0)
{
    if(L == R)
    {
        h[P].clear();
        h[P].add(-L ,(L-1LL)*SumA[L-1]-SumAi[L-1]);
        return;
    }
 
    int Mid = (L+R)>>1;
 
    Build(L  ,Mid ,FL(P));
    Build(Mid+1 ,R ,FR(P));
    Merge(P ,FL(P) ,FR(P));
}
 
long long Query(long long x ,int QL ,int QR ,int L=1 ,int R=N ,int P=0)
{
    if(R < QL || QR < L)
        return -9e18;
    if(QL <= L && R <= QR)
        return h[P].eval(x);
 
    int Mid = (L+R)>>1;
 
    return max(Query(x ,QL ,QR ,L     ,Mid ,FL(P))
              ,Query(x ,QL ,QR ,Mid+1 ,R   ,FR(P)));
}
 
long long Solve()
{
    for(int i=1; i<=N; i++)
    {
        SumA[i] = SumA[i-1]+A[i];
        SumAi[i] = SumAi[i-1]+(A[i]*1LL*i);
    }
 
    Build();
 
    long long Ans = 0LL;
    for(int i=1; i<=N; i++)
        Ans += Query(SumA[i] ,i-R[i]+1 ,i)+SumA[i]+SumAi[i];
    return Ans;
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
 
        printf("%I64d\n",GM(Solve()));
    }
}

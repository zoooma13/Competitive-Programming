/**
same editorial idea : https://codeforces.com/blog/entry/63436
*/

#include <bits/stdc++.h>
using namespace std;

#define MAX_N 100005
#define MAX_K 300005

int N ,M ,K;
int L ,R ,P;
int A ,B ,X ,Y;
vector <pair<pair<int ,int> ,int>> Segs;

int root[MAX_K];
int le[MAX_K*20] ,ri[MAX_K*20] ,va[MAX_K*20] ,nn;
void Insert(int&p ,int la ,int i ,int v ,int L=0 ,int R=N-1)
{
    if(!p) p = ++nn;
    if(L == R){
        va[p] = v;
        if(la)
            va[p] = min(va[p] ,va[la]);
        return;
    }

    int Mid = (L+R)>>1;
    if(i <= Mid){
        ri[p] = (ri[p] ? ri[p] : ri[la]);
        Insert(le[p] ,le[la] ,i ,v ,L   ,Mid);
    } else {
        le[p] = (le[p] ? le[p] : le[la]);
        Insert(ri[p] ,ri[la] ,i ,v ,Mid+1 ,R);
    }
    va[p] = max(va[le[p]] ,va[ri[p]]);
}
int query(int&p ,int QL ,int QR ,int L=0 ,int R=N-1)
{
    if(R < QL || QR < L)
        return -2e9;
    if(QL <= L && R <= QR)
        return va[p];

    int Mid = (L+R)>>1;
    return max(query(le[p] ,QL ,QR ,L ,Mid)
              ,query(ri[p] ,QL ,QR ,Mid+1 ,R));
}
int main()
{
    scanf("%d%d%d",&N,&M,&K);

    for(int i=0; i<K; i++){
        scanf("%d%d%d",&L,&R,&P);
        Segs.push_back({{L ,R} ,P-1});
    }

    for(int i=0; i<N; i++)
        Insert(root[K] ,0 ,i ,2e9);
    sort(Segs.begin() ,Segs.end());
    for(int i=K-1; ~i; i--)
        Insert(root[i] ,root[i+1] ,Segs[i].second ,Segs[i].first.second);

    while(M--)
    {
        scanf("%d%d%d%d",&A,&B,&X,&Y);
        int idx = lower_bound(Segs.begin() ,Segs.end() ,make_pair(make_pair(X ,0) ,0)) - Segs.begin();
        int ans = query(root[idx] ,A-1 ,B-1);
        printf(ans <= Y ? "yes\n" : "no\n");
        fflush(stdout);
    }
}

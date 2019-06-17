/**
tags : persistent segment tree ,sqrt decomposition
time complexity : O((n+q)*sqrtn*logn)
*/

#include <bits/stdc++.h>
using namespace std;

#define MAX_N 300005
#define SQRT_N 300
#define all(v) v.begin() ,v.end()
#define lb lower_bound
#define ub upper_bound

const int mod = 1e9+7;
int modinv(int a){
    int x = 1 ,p = mod-2;
    for( ; p; p>>=1){
        if(p & 1)
            x = 1LL*x*a%mod;
        a = 1LL*a*a%mod;
    }
    return x;
}

int fact[MAX_N];

int n ,q;
int s[MAX_N];
int l1 ,l2 ,r1 ,r2;
vector <int> occ[MAX_N] ,big;

int root[MAX_N] ,lf[25*MAX_N] ,ri[25*MAX_N] ,va[25*MAX_N] ,nn;
void bld(int&p ,int l=0 ,int r=n-1){
    if(!p) p = ++nn;
    va[p] = 1;
    if(l == r) return;
    int mid = (l+r)>>1;
    bld(lf[p] ,l ,mid);
    bld(ri[p] ,mid+1 ,r);
}
void upd(int&p ,int i ,int v ,int l=0 ,int r=n-1){
    if(!p) p = ++nn;
    if(l == r){
        va[p] = v;
        return;
    }
    int mid = (l+r)>>1;
    if(i <= mid) upd(lf[p] ,i ,v ,l ,mid);
    else         upd(ri[p] ,i ,v ,mid+1 ,r);
}
void mrg(int&lp ,int&p){
    if(lf[p]) mrg(lf[lp] ,lf[p]);
    else      lf[p] = lf[lp];
    if(ri[p]) mrg(ri[lp] ,ri[p]);
    else      ri[p] = ri[lp];
    if(lf[p]&&ri[p])
        va[p] = 1LL*va[lf[p]]*va[ri[p]]%mod;
}
int qry(int&p ,int i ,int l=0 ,int r=n-1){
    if(i <= l)
        return va[p];
    if(r < i)
        return 1;
    int mid = (l+r)>>1;
    return 1LL*qry(lf[p] ,i ,l ,mid)*qry(ri[p] ,i ,mid+1 ,r)%mod;
}

int main()
{
    fact[0] = 1;
    for(int i=1; i<MAX_N; i++)
        fact[i] = 1LL*fact[i-1]*i%mod;

    scanf("%d%d",&n,&q);
    map <int ,int> com;
    for(int i=0; i<n; i++)
        scanf("%d",&s[i]) ,com[s[i]];
    int idx = 0;
    for(auto&p : com)
        p.second = idx++;
    for(int i=0; i<n; i++){
        s[i] = com[s[i]];
        occ[s[i]].push_back(i);
    }

    bld(root[0]); va[0] = 1;
    for(int i=0; i<n; i++){
        root[i+1] = ++nn;
        if(occ[s[i]].size() > SQRT_N){
            if(find(big.begin() ,big.end() ,s[i]) == big.end())
                big.push_back(s[i]);
        }
        else{
            int vf = lb(all(occ[s[i]]) ,i)-occ[s[i]].begin()+1;
            for(int j=0; vf; j++)
                upd(root[i+1] ,occ[s[i]][j] ,vf--);
        }
        mrg(root[i] ,root[i+1]);
    }

    int last_ans = 0;
    while(q--){
        scanf("%d%d%d%d",&l1,&l2,&r1,&r2);
        l2 = (1LL*l1*last_ans+l2)%n ,r2 = (1LL*r1*last_ans+r2)%n;
        if(l2 > r2)
            swap(l2 ,r2);

        int ans = 1 ,cntb;
        for(int&b : big){
            cntb = ub(all(occ[b]) ,r2)-lb(all(occ[b]) ,l2);
            ans = 1LL*ans*fact[cntb]%mod;
        }

        ans = 1LL*ans*qry(root[r2+1] ,l2)%mod;
        last_ans = 1LL*fact[r2-l2+1]*modinv(ans)%mod;
        printf("%d\n",last_ans);
    }
}

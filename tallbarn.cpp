/**
Editorial's solution
*/
#include <bits/stdc++.h>
using namespace std;

#define MAX_N 100005

int N; long long K;
long long A[MAX_N];

long long can(double x)
{
    long long ret = 0;
    for(int i=0; i<N; i++)
        ret += (-1 + sqrt(1 + 4*A[i]/x)) / 2;
    return ret;
}

int main()
{
    freopen("tallbarn.in" ,"r" ,stdin);
    freopen("tallbarn.out" ,"w" ,stdout);

    scanf("%d%lld",&N,&K); K-=N;
    for(int i=0; i<N; i++)
        scanf("%lld",&A[i]);

    double st = 0 ,en = 1e18 ,mid;
    for(int i=0; i<200; i++)
    {
        mid = (st+en)/2;
        if(can(mid) >= K)
            st = mid;
        else
            en = mid;
    }

    double Ans = 0;
    long long Cows = 0;

    for(int i=0; i<N; i++)
    {
        long long C = (-1 + sqrt(1 + 4*A[i]/st)) / 2;
        Ans += A[i]/(C+1.00);
        Cows += C;
    }

    cout << (long long)round(Ans - (K-Cows)*st) << endl;
}

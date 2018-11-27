/**
same editorial idea : https://codeforces.com/blog/entry/62797
*/

#include <bits/stdc++.h>
using namespace std;

#define MAX_N 300005

const int MOD = 1e9+7;
int GM(long long Num){
    Num += (Num < 0 ? MOD : 0);
    return Num == MOD ? MOD : Num%MOD;
}

int lprime[MAX_N];
void sieve(){
    for(int i=2; i<MAX_N; i++) if(!lprime[i])
    for(int j=i; j<MAX_N; j+=i)
        lprime[j] = (!lprime[j] ? i : lprime[j]);
}
vector <int> divs(int Num){
    vector <int> ret;
    while(Num != 1){
        int x = lprime[Num];
        while(Num % x == 0)
            Num /= x;
        ret.push_back(x);
    }
    return ret;
}

int can[MAX_N];
void Add(vector <int> d ,int i=0 ,int p=1){
    if(i == d.size()){
        can[p]++;
        return;
    }

    Add(d ,i+1 ,p);
    Add(d ,i+1 ,p*d[i]);
}

int modInv(int A ,int B=MOD-2){
	long long X = 1, Y = A;
	for( ; B>0; B>>=1){
		if (B & 1)
			X = GM(X*Y);
		Y = GM(Y*Y);
	}
	return GM(X);
}
int C(int n ,int r){
    if(n < r) return 0;
    long long rf = 1 ,nf = 1;
    for(int i=1; i<=r; i++)
        rf *= i;
    for(int i=n; i>(n-r); i--)
        nf = GM(nf*i);
    return GM(nf * modInv(rf));
}

int N;
int A[MAX_N];

int main()
{
    sieve();

    scanf("%d",&N);

    int gc = 0;
    for(int i=0; i<N; i++)
    {
        scanf("%d",&A[i]);
        gc = __gcd(gc ,A[i]);
        Add(divs(A[i]));
    }

    if(gc > 1){
        printf("-1\n");
        return 0;
    }

    int ans = 7 ,dp[MAX_N];
    for(int i=6; i>=1; i--)
    {
        memset(dp ,0 ,sizeof dp);
        for(int j=MAX_N-5; j > 0; j--)
        {
            dp[j] = C(can[j] ,i);

            for(int l=2*j; l<MAX_N; l+=j)
                dp[j] = GM(dp[j] - dp[l]);
        }

        if(dp[1])
            ans = i;
    }

    printf("%d\n",ans);
}

/**
editorial : https://codeforces.com/blog/entry/67614
time complexity : O(logn)
*/

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9+7;

#define matrix vector<vector<int>>
matrix operator*(matrix a ,matrix b){
    matrix c(a.size() ,vector<int>(b[0].size() ,0));
    for(int i=0; i<a.size(); i++)
    for(int k=0; k<b.size(); k++)
    for(int j=0; j<b[0].size(); j++)
        c[i][j] = (c[i][j] + (a[i][k]*1LL*b[k][j])%(MOD-1))%(MOD-1);
    return c;
}
matrix operator^(matrix a ,long long p){
    matrix x(a.size() ,vector<int>(a.size() ,0));
    for(int i=0; i<a.size(); i++)
        x[i][i] = 1;
    for( ; p; p>>=1){
		if(p & 1)
			x = x*a;
		a = a*a;
	}
    return x;
}

int dv(int num ,int p){
    if(p == 1)
        return 0;
    int ret = 0;
    while(num%p == 0)
        ret++ ,num /= p;
    return ret;
}
int powmod(int a ,long long p){
    int x = 1;
    for( ; p; p>>=1){
		if(p & 1)
			x = (1LL*x*a)%MOD;
		a = (1LL*a*a)%MOD;
	}
    return x;
}

int main()
{
    long long n;
    int f1 ,f2 ,f3 ,c;
    cin >> n >> f1 >> f2 >> f3 >> c;

    int ans = 1;
    for(auto&p : set<int>{f1 ,f2 ,f3 ,c})
    {
        matrix x = {{1 ,1 ,1},
                    {1 ,0 ,0},
                    {0 ,1 ,0}};
        matrix y = {{dv(f3 ,p)+3*dv(c ,p)},
                    {dv(f2 ,p)+2*dv(c ,p)},
                    {dv(f1 ,p)+1*dv(c ,p)}};

        int tot_p = (-n*dv(c ,p))%(MOD-1)+MOD-1 + ((x^(n-3))*y)[0][0];
        ans = (1LL * ans * powmod(p ,tot_p%(MOD-1)))%MOD;
    }

    cout << ans << endl;
}

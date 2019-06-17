/**
tags : math
*/

#include <bits/stdc++.h>
using namespace std;

const long long mod = 1e9+7 ,modinv_2 = 500000004;

int main()
{
    int t;
    cin >> t;
    while(t--){
        long long n ,k;
        cin >> n >> k;
        long long ck = (k+n-2)/(n-1)%mod;
        cout << ((ck*((k-1)%mod)%mod-ck*(ck-1)%mod*modinv_2%mod*((n-1)%mod)%mod)+mod)%mod << endl;
    }
}

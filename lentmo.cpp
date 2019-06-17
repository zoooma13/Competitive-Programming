/**
tags : ad-hoc ,xor
time complexity : O(n)
*/

#include <bits/stdc++.h>
using namespace std;

#define MAX_N 10004

int t;
int n ,k ,x;
int a[MAX_N];

int main()
{
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        for(int i=0; i<n; i++)
            scanf("%d",&a[i]);
        scanf("%d%d",&k,&x);

        if(k == n){
            long long ch0 = 0 ,ch1 = 0;
            for(int i=0; i<n; i++)
                ch0 += a[i] ,ch1 += (a[i]^x);
            cout << max(ch0 ,ch1) << endl;
            continue;
        }

        int mi[] = {INT_MAX ,INT_MAX} ,gtch = 0;
        long long ans = 0LL;
        for(int i=0; i<n; i++){
            bool ch = (a[i]^x) > a[i]; gtch += ch;
            mi[ch] = min(mi[ch] ,abs((a[i]^x)-(a[i])));
            ans += max(a[i]^x ,a[i]);
        }

        if(k%2 == 0 && gtch%2 == 1)
            cout << ans - min(mi[0] ,mi[1]) << endl;
        else
            cout << ans << endl;
    }
}

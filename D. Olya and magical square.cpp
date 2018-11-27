/**
its easier to take the path which is to the very left and to the top of all squares.
----
|OOO
|OOO
|OOO
number of operations required to split a square of size 2^n by 2^n into squares of size 1 = (4^n-1) / 3
if n > 31 we can do 1 operation on the whole square and then do the rest of operations
on the bottom right square because (4^32 -1)/3 > k(10^18).
else we can keep doing operations on the squares which our path crosses until it can't do all of path's squares
then we do split the other squares of different sizes that we split before and not on the path.
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin >> t;

    auto mxops = [](int n){
        return ((1LL << (2*n)) - 1) / 3;
    };

    while(t--)
    {
        long long n ,k;
        cin >> n >> k;

        if(n > 31)
            cout << "YES" << ' ' << n-1 << endl;
        else if(k > mxops(n))
            cout << "NO" << endl;
        else
        {
            int N = n;
            long long atcor = 1;
            long long ofsize[35];

            while(k-atcor >= 0 && N > 0)
            {
                ofsize[--N] = 2*atcor-1;
                k -= atcor;
                atcor = 2*atcor+1;
            }

            unsigned long long split = 0;
            while(n-- && split < k)
                split += 1ull*mxops(n)*ofsize[n];

            if(split >= k)
                cout << "YES" << ' ' << N << endl;
            else
                cout << "NO" << endl;
        }
    }
}

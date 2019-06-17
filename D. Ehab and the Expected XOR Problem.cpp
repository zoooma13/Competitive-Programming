/**
editorial : https://codeforces.com/blog/entry/67388
tags : bitmasks ,ad-hoc
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n ,x;
    cin >> n >> x; x = 1<<(int)log2(x);

    vector <int> ans;
    for(int i=1; i<(1<<n); i=2*i+1){
        if(x&((i+1)>>1))
            continue;
        ans.push_back(i);
        ans.insert(ans.end() ,ans.begin() ,ans.end());
        ans.pop_back();
    }

    cout << ans.size() << endl;
    for(int&i : ans)
        cout << i << ' ';
    cout << endl;
}

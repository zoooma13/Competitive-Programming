/**
same editorial idea
https://codeforces.com/blog/entry/56920
*/

#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

int N ,K;
int P[16];

vector <ull> part1{1} ,part2{1};
void GetNums(vector <int> primes ,vector<ull>&part)
{
    for(int i : primes)
    {
        vector <ull> add;

        for(ull cur = i; cur < 1e18; cur *= i)
        {
            ull can = ceil(1e18/cur);

            for(auto&j : part)
            {
                if(can < j)
                    break;
                add.push_back(j*cur);
            }

            if(ceil(1e18/cur) < i)
                break;
        }

        part.insert(part.end() ,add.begin() ,add.end());
        sort(part.begin() ,part.end());
    }
}

int main()
{
    cin >> N;
    for(int i=0; i<N; i++)
        cin >> P[i];
    cin >> K;

    vector <int> prim1{P ,P+(N/2)};
    vector <int> prim2{P+(N/2) ,P+N};
    GetNums(prim1 ,part1);
    GetNums(prim2 ,part2);

    auto Less = [](long long X){
        int ret = 0;
        for(auto&i : part2)
            ret += upper_bound(part1.begin() ,part1.end() ,X/i) - part1.begin();
        return ret;
    };

    long long st = 0 ,en = 1e18 ,mid;
    while(st <= en)
    {
        mid = (st+en)>>1;
        if(Less(mid) >= K)
            en = mid-1;
        else
            st = mid+1;
    }

    cout << en+1 << endl;
}

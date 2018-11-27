/**
same editorial idea : https://codeforces.com/blog/entry/63384
*/

#include <bits/stdc++.h>
using namespace std;

#define MAX_N 100005

const int MOD = 1e9+7;
int GM(long long Num){
    return Num%MOD;
}

int N;
long long X ,Y;
int L[MAX_N] ,R[MAX_N];

map <int ,int> mp;
vector <int> At[2*MAX_N];

int main()
{
    scanf("%d%d%d",&N,&X,&Y);
    for(int i=1; i<=N; i++)
        scanf("%d%d",&L[i],&R[i]) ,mp[L[i]] ,mp[R[i]];

    int nn = 0;
    for(auto&i : mp)
        i.second = nn++;
    for(int i=1; i<=N; i++){
        At[mp[L[i]]].push_back(i);
        At[mp[R[i]]].push_back(-i);
    }

    long long Ans = 0LL;
    priority_queue <int> last;
    for(int i=0; i<nn; i++)
    {
        sort(At[i].begin() ,At[i].end() ,greater<int>());

        for(int j : At[i])
        {
            if(j > 0)
            {
                long long Past = 1e18;
                if(!last.empty())
                    Past = Y*(L[j]-last.top()+1LL);

                long long toadd = Y*(R[j]-L[j]);
                if(X < Past){
                    Ans = GM(Ans + GM(X+toadd));
                }else{
                    Ans = GM(Ans + GM(Past+toadd));
                    last.pop();
                }
            }
            else
                last.push(R[-j]+1);
        }
    }

    cout << Ans << endl;
}

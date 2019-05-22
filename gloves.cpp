/**
same editorial's idea : https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/Baltic/official/boi2008_solutions/gloves-sol-en.pdf
*/

#include <bits/stdc++.h>
using namespace std;
 
#define pll pair<long long ,long long>
 
int N;
long long A[20] ,B[20];
 
int main()
{
    cin >> N;
    for(int i=0; i<N; i++)
        cin >> A[i];
    for(int i=0; i<N; i++)
        cin >> B[i];
 
    vector <pll> vll ,tll;
    for(int b=0; b<(1<<N); b++)
    {
        long long opA = 0LL ,opB = 0LL;
        for(int i=0; i<N; i++){
            if(b&(1<<i))
                opA += A[i];
            else
                opB += B[i];
        }
        vll.push_back({opA ,opB});
    }
 
    sort(vll.begin() ,vll.end() ,greater<pll>());
    long long mxs = -1LL;
    for(auto&p : vll){
        if(p.second > mxs)
            tll.push_back({p.second ,p.first});
        mxs = max(mxs ,p.second);
    }vll.clear();
    sort(tll.begin() ,tll.end() ,greater<pll>());
    mxs = -1LL;
    for(auto&p : tll){
        if(p.second > mxs)
            vll.push_back(p);
        mxs = max(mxs ,p.second);
    }
 
    long long ansA = 1e18 ,ansB = 1e18;
    for(int i=1; i<vll.size(); i++)
        if(vll[i-1].second+1+vll[i].first+1 < ansA+ansB){
            ansA = vll[i-1].second+1;
            ansB = vll[i].first+1;
    }
 
    cout << ansA << endl;
    cout << ansB << endl;
}

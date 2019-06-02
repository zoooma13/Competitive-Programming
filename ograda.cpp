/**
same as editorial : https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/COCI/official/2010/contest4_solutions/solutions.pdf
*/

#include <bits/stdc++.h>
using namespace std;

#define MAX_N 1000006

int n ,x;
int a[MAX_N] ,mi_x[MAX_N];
pair <int ,int> max_mi[MAX_N];

int main()
{
    scanf("%d%d",&n,&x);
    for(int i=0; i<n; i++)
        scanf("%d",&a[i]);

    multiset <int> ms;
    for(int i=n-x; i<n; i++)
        ms.insert(a[i]);
    mi_x[n-x] = *ms.begin();
    for(int i=n-x-1; ~i; i--){
        ms.erase(ms.find(a[i+x]));
        ms.insert(a[i]);
        mi_x[i] = *ms.begin();
    }

    int st = n-x;
    set <pair<int ,int>> rng;
    rng.insert({mi_x[st] ,st});
    max_mi[n-1] = *prev(rng.end());
    for(int i=n-2; ~i; i--){
        if(--st >= 0)
            rng.insert({mi_x[st] ,st});
        if(i+x < n)
            rng.erase({mi_x[i+1] ,i+1});
        max_mi[i] = *prev(rng.end());
    }

    pair <int ,int> pp;
    long long area = 0 ,swoop = 0;
    for(int i=0; i<n; i++){
        area += a[i]-max_mi[i].first;
        if(max_mi[i].first > pp.first || i >= pp.second){
            pp = {max_mi[i].first ,max_mi[i].second+x};
            swoop++;
        }
    }
    cout << area << endl << swoop << endl;
}

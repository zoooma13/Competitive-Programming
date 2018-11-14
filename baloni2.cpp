/**
observations :
 1 - there is only one path for the arrow to cross
     (in a given set of ballons)
 2 - its always better to shoot the higher ballons first
     as it will pop other ballons on its way.
     
so we can easily simulate the arrows move starting by the 
highest ballon height ad decreasing the until all the ballons
are popped
     
time complexity : O(NlogN)
*/

#include <bits/stdc++.h>
using namespace std;

#define MAX_N 1000006

int N ,A;
set <int> ss[MAX_N];

int cnt[MAX_N];
vector <int> nxt;

int main()
{
    scanf("%d",&N);
    for(int i=0; i<N; i++)
    {
        scanf("%d",&A);
        ss[A].insert(i);
        if(!cnt[A]++)
            nxt.push_back(A);
    }

    sort(nxt.begin() ,nxt.end());

    int Ans = 0;
    for(int pt = nxt.size()-1; ~pt;)
    {
        int i = nxt[pt] ,j = -1;

        while(true)
        {
            auto it = ss[i].upper_bound(j);
            if(it == ss[i].end())
                break;

            j = *it;
            ss[i].erase(it);
            --cnt[i--];
        }
        while(~pt && !cnt[nxt[pt]])
            pt--;

        Ans++;
    }
    cout << Ans << endl;
}

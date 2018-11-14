/**
greedy approach :
moving by order from left to right
if the packages claimed before >= B[i] then add this order to the ans
else if the largest package order in the selected orders > B[i]
then remove it from orders and add B[i] instead
this can be simulated using set and priority_queue
*/
#include <bits/stdc++.h>
using namespace std;

#define MAX_N 250005

int N;
int A[MAX_N];
int B[MAX_N];

priority_queue <pair<int ,int> > pq;

int main()
{
    scanf("%d",&N);
    for(int i=0; i<N; i++)
        scanf("%d",&A[i]);
    for(int i=0; i<N; i++)
        scanf("%d",&B[i]);

    set <int> Ans;
    long long S = 0LL;
    for(int i=0; i<N; i++)
    {
        S += A[i];
        if(S >= B[i])
        {
            S -= B[i];
            pq.push({B[i] ,i+1});
            Ans.insert(i+1);
        }
        else if(!pq.empty() && pq.top().first >= B[i])
        {
            S = S + pq.top().first - B[i];
            Ans.erase(pq.top().second);
            Ans.insert(i+1);
            pq.pop();
            pq.push({B[i] ,i+1});
        }
    }

    cout << Ans.size() << endl;
    for(int i : Ans)
        cout << i << ' ';
    cout << endl;
}

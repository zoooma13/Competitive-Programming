#include <bits/stdc++.h>
using namespace std;

#define MAX_N 200005
#define MAX_M 502

int N ,M;
int A ,B;
int Mem[MAX_N];
vector <int> Adj[MAX_N];

vector <int> knap(vector<int>&a ,vector<int> b)
{
    vector <int> c(min(M+1 ,(int)(a.size()+b.size())) ,0);
    for(int i=0; i<a.size(); i++)
    for(int j=0; j<b.size() && i+j<=M; j++)
        c[i+j] = max(c[i+j] ,a[i]+b[j]);
    return c;
}
vector <int> Solve(int v)
{
    vector <int> ans = {0 ,0};
    for(int i : Adj[v])
        ans = knap(ans ,Solve(i));
    ans[1] = max(ans[1] ,Mem[v]);
    return ans;
}

int main()
{
    scanf("%d%d",&N,&M);

    int root;
    for(int i=1; i<=N; i++)
    {
        scanf("%d%d",&A,&B);

        Mem[i] = B;
        if(A == 0)
            root = i;
        else
            Adj[A].push_back(i);
    }

    printf("%d\n",Solve(root)[M]);
}

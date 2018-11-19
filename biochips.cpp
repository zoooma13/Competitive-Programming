/**
Problem description : 
  given a tree with numbers written on nodes choose exactly m nodes 
  such that no two chosen nodes(u ,v) and u is ancestor of v. 
  maximize sum of values of chosen nodes.

we can represent answer of a subtree as vector where element at index i[0,M] represent the
maximum answer of choosing exactly i nodes.
ex : answer[1] = maximum node in the subtree

we can see that the answer for any node depends on the answers of its children subtrees
so we want to merge the answers of children to get the best answer for the current subtree.

now it's a knapsack problem we have some items with weights(represented by index) and values(elements)
and we want to maximize the vaues at each index of the new answer vector.

implemetation details : 
  in function knap we merge two vectors into new vector where the value of k-th item is max of all i,j
  where i+j = k and a[i]+b[j] is max
  In worst case this function works in O(M^2) which can only happen at most N/M = (N/M)*M^2 = NM
  on average it works in O(M) which gives us complexity N*M

time complexity : O(NM)
*/
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

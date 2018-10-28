/**
construct graph from intersection of vertical and horizontal dangos
and for each connected component find the max number vertices that
can be marked such that no two vertices are adjacent (MIS)

Wrong approach used in code :
  for each connected component color the graph with two colors
  such that no two adjacent nodes are of the same color,
  the color with the max number of nodes is the best answer
  for this connected component.

Correct approach : N/A

Special properties of the graph :
  1) each node can have at most 3 adjacent nodes (max_degree = 3)
  2) cycles can only be of length four
*/

#include <bits/stdc++.h>
using namespace std;

#define MAX_N 3005

int N ,M;
char G[MAX_N][MAX_N];

vector <int> Adj[MAX_N*MAX_N];

int idx = 0;
int id1[MAX_N][MAX_N];
int id2[MAX_N][MAX_N];

bool vis[MAX_N*MAX_N];
int Ev ,Od;

void DFS(int Q ,bool S)
{
    Ev += !S ,Od += S;
    vis[Q] = 1;

    for(int&i : Adj[Q])
        if(!vis[i])
            DFS(i ,!S);
}

int main()
{
    scanf("%d%d",&N,&M);
    for(int i=0; i<N; i++)
        scanf("%s",G[i]);

    for(int i=0; i<N; i++)
    for(int j=0; j<M-2; j++)
        if(G[i][j] == 'R' && G[i][j+1] == 'G' && G[i][j+2] == 'W')
            id1[i][j] = id1[i][j+1] = id1[i][j+2] = ++idx;

    for(int i=0; i<N-2; i++)
    for(int j=0; j<M; j++)
        if(G[i][j] == 'R' && G[i+1][j] == 'G' && G[i+2][j] == 'W')
            id2[i][j] = id2[i+1][j] = id2[i+2][j] = ++idx;

    for(int i=0; i<N; i++)
    for(int j=0; j<M; j++)
        if(id1[i][j] != id2[i][j] && min(id1[i][j] ,id2[i][j]) != 0)
        {
            Adj[id1[i][j]].push_back(id2[i][j]);
            Adj[id2[i][j]].push_back(id1[i][j]);
        }

    int Ans = 0;
    for(int i=1; i<=idx; i++)
    {
        Ev = 0 ,Od = 0;
        if(!vis[i])
            DFS(i ,0);
        Ans += max(Ev ,Od);
    }

    printf("%d\n",Ans);
}

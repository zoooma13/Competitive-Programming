/**
same editorial idea : https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/Baltic/official/boi2012_solutions/peaks-sol.pdf
*/

#include <bits/stdc++.h>
using namespace std;

#define MAX_N 2003
#define MAX_NM 100005

const int di[] = {0 ,-1 ,-1 ,-1 ,0 ,1 ,1 ,1};
const int dj[] = {-1 ,-1 ,0 ,1 ,1 ,1 ,0 ,-1};

int N ,M;
int E[MAX_N][MAX_N];

int He[MAX_NM];
int Room[MAX_N][MAX_N] ,Ro = 1;

bool vis[MAX_N][MAX_N];
void dfs(int i ,int j)
{
    vis[i][j] = 1 ,Room[i][j] = Ro;
    for(int l=0; l<8; l++)
        if(0 <= i+di[l] && i+di[l] < N && 0 <= j+dj[l] && j+dj[l] < M)
        if(E[i][j] == E[i+di[l]][j+dj[l]] && !vis[i+di[l]][j+dj[l]])
            dfs(i+di[l] ,j+dj[l]);
}

int Ans[MAX_NM];
int Parent[MAX_NM];
int Find(int U){
    return Parent[U] = (Parent[U] == U ? U : Find(Parent[U]));
}
void Union(int A ,int B ,int C){
    A = Find(A) ,B = Find(B);
    if(A == B)
        return;

    if(He[A] == He[B]){
        Parent[A] = B;
        Ans[A] = -B;
    }
    else if(He[A] < He[B]){
        Parent[A] = B;
        Ans[A] = C;
    }
    else if(He[A] > He[B]){
        Parent[B] = A;
        Ans[B] = C;
    }
}
int GetAns(int B){
    if(Ans[B] < 0)
        return Ans[B] = GetAns(-Ans[B]);
    return Ans[B];
}

int main()
{
    scanf("%d%d",&N,&M);
    for(int i=0; i<N; i++)
    for(int j=0; j<M; j++)
        scanf("%d",&E[i][j]);

    for(int i=0; i<N; i++)
    for(int j=0; j<M; j++)
        if(!vis[i][j])
            dfs(i ,j) ,He[Ro] = E[i][j] ,Ro++;

    set <int> Adj[Ro];
    for(int i=0; i<N; i++)
    for(int j=0; j<M; j++)
    for(int l=0; l<8; l++)
        if(0 <= i+di[l] && i+di[l] < N && 0 <= j+dj[l] && j+dj[l] < M)
        if(Room[i][j] != Room[i+di[l]][j+dj[l]]){
            Adj[Room[i][j]].insert(Room[i+di[l]][j+dj[l]]);
            Adj[Room[i+di[l]][j+dj[l]]].insert(Room[i][j]);
        }

    vector <int> P(Ro-1);
    iota(P.begin() ,P.end() ,1);
    sort(P.begin() ,P.end() ,[](int&i ,int&j){
         return He[i] > He[j];
    });

    iota(Parent ,Parent+Ro ,0);
    for(int&i : P)
    for(auto&j : Adj[i])
        if(He[i] <= He[j])
            Union(i ,j ,He[i]);

    vector <pair<int ,int>> vv;
    for(int&i : P){
        bool isPeak = 1;
        for(auto&j : Adj[i])
            isPeak &= (He[i] >= He[j]);
        if(isPeak)
            vv.push_back({He[i] ,GetAns(i)});
    }

    sort(vv.begin() ,vv.end() ,greater<pair<int ,int>>());
    printf("%d\n",vv.size());
    for(auto&i : vv)
        printf("%d %d\n",i.first,i.second);
}

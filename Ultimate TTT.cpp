/**
simulate the process of two players and choose the optimal move using backtrack
*/

#include <bits/stdc++.h>
using namespace std;

int N ,M;
string G[5];

bool full(int&Y1 ,int&Y2 ,int&X1 ,int&X2){
    for(int i=Y1; i<=Y2; i++)
    for(int j=X1; j<=X2; j++)
        if(G[i][j] == 2)
            return 0;
    return 1;
}
int win(int&Y1 ,int&Y2 ,int&X1 ,int&X2){
    for(int i=Y1; i<=Y2; i++)
    for(int j=X1; j<=X2-2; j++)
        if(G[i][j] == G[i][j+1] && G[i][j] == G[i][j+2] && G[i][j] != 2)
            return G[i][j];
    for(int i=Y1; i<=Y2-2; i++)
    for(int j=X1; j<=X2; j++)
        if(G[i][j] == G[i+1][j] && G[i][j] == G[i+2][j] && G[i][j] != 2)
            return G[i][j];
    if(G[Y1][X1] == G[Y1+1][X1+1] && G[Y1+1][X1+1] == G[Y1+2][X1+2] && G[Y1+1][X1+1] != 2)
        return G[Y1+1][X1+1];
    if(G[Y1+2][X1] == G[Y1+1][X1+1] && G[Y1+1][X1+1] == G[Y1][X1+2] && G[Y1+1][X1+1] != 2)
        return G[Y1+1][X1+1];
    if(full(Y1 ,Y2 ,X1 ,X2))
        return 2;
    return 3;
}

pair<int ,int> WW = {-1 ,-1} ,TT = {-1 ,-1};
int solve(int Y1 ,int Y2 ,int X1 ,int X2 ,bool T);
int go(int&Y1 ,int&Y2 ,int&X1 ,int&X2 ,int&I ,int&J ,bool&T)
{
    int y1 = 5 ,y2 = -1 ,x1 = 5 ,x2 = -1;
    G[I][J] = T;
    for(int i=Y1; i<=Y2; i++)
    for(int j=X1; j<=X2; j++)
        if(G[i][j] != 2)
            y1 = min(y1 ,i) ,x1 = min(x1 ,j) ,y2 = max(y2 ,i) ,x2 = max(x2 ,j);
    int W = solve(max(0,y2-2) ,min(N-1,y1+2) ,max(0,x2-2) ,min(M-1,x1+2) ,!T);
    G[I][J] = 2;
    return W;
}
int solve(int Y1 ,int Y2 ,int X1 ,int X2 ,bool T)
{
    if(win(Y1 ,Y2 ,X1 ,X2) != 3)
        return win(Y1 ,Y2 ,X1 ,X2);

    pair <int ,int> ti = {-1 ,-1} ,wn = {-1 ,-1};
    for(int i=Y2; i>=Y1; i--)
    for(int j=X2; j>=X1; j--)
        if(G[i][j] == 2)
        {
            int W = go(Y1 ,Y2 ,X1 ,X2 ,i ,j ,T);
            if(W == (int)T)
                wn = {i ,j};
            if(W == 2)
                ti = {i ,j};
        }

    WW = wn ,TT = ti;
    if(~wn.first)
        return T;
    if(~ti.first)
        return 2;
    return !T;
}

int main()
{
    int xs = 0 ,os = 0;

    cin >> N >> M;
    for(int i=0; i<N; i++){
        cin >> G[i];
        xs += count(G[i].begin() ,G[i].end() ,'X');
        os += count(G[i].begin() ,G[i].end() ,'O');
        for(char&c : G[i])
            c = (c == 'X' ? 0 : (c == 'O' ? 1 : 2));
    }

    solve(0 ,N-1 ,0 ,M-1 ,!(xs == os));
    if(~WW.first)
        cout << WW.first+1 << ' ' << WW.second+1 << endl;
    else if(~TT.first)
        cout << TT.first+1 << ' ' << TT.second+1 << endl;
    else
    {
        for(int i=0; i<N; i++)
        for(int j=0; j<M; j++)
            if(G[i][j] == 2){
                cout << i+1 << ' ' << j+1 << endl;
                return 0;
            }
    }
}

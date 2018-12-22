/**
editorial : https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/Baltic/official/boi2012_solutions/melody-sol.pdf
*/

#include <bits/stdc++.h>
using namespace std;

#define MAX_N 102
#define MAX_L 100005

int N ,G ,S;
char ss[MAX_N];
string Nt[MAX_N];
int L;
int A[MAX_L];

int main()
{
    scanf("%d%d%d",&N,&G,&S);
    for(int i=0; i<N; i++)
        scanf("%s",ss) ,Nt[i] = ss;
    scanf("%d",&L);
    for(int i=0; i<L; i++)
        scanf("%d",&A[i]) ,A[i]--;

    auto diff = [](int i ,int j){
        int ret = 0;
        for(int l=0; l<G; l++)
            ret += (Nt[i][l] != Nt[j][l]);
        return ret;
    };

    vector<vector<int>> dist(N ,vector<int>(N ,1e9));
    vector<vector<int>> par(N ,vector<int>(N ,-1));
    for(int i=0; i<N; i++)
    for(int j=0; j<N; j++)
        if(diff(i ,j) <= S)
            dist[i][j] = 1 ,par[i][j] = i;

    for(int s=0; s<N; s++)
    {
        queue <int> q;
        for(int i=0; i<N; i++)
            if(dist[s][i] == 1)
                q.push(i);

        while(!q.empty()){
            int t = q.front(); q.pop();
            for(int i=0; i<N; i++)
                if(dist[s][i] == 1e9 && dist[t][i] == 1){
                    par[s][i] = t;
                    dist[s][i] = dist[s][t]+1;
                    q.push(i);
                }
        }
    }

    auto get_path = [&](int fr ,int to ,int len){
        fr = A[fr] ,to = A[to];
        vector <int> ret(len-dist[fr][to] ,fr) ,ret2 = {to};

        for( ; par[fr][to] != fr; to = par[fr][to])
            ret2.push_back(par[fr][to]);
        while(!ret2.empty())
            ret.push_back(ret2.back()) ,ret2.pop_back();

        return ret;
    };

    vector <int> dp(L ,1) ,prv(L ,-1);
    vector <vector<int>> lst(N ,vector<int>());
    for(int i=0; i<L; i++)
    {
        for(int j=0; j<N; j++)
        {
            int k = upper_bound(lst[j].begin() ,lst[j].end() ,i-dist[A[i]][j])-lst[j].begin()-1;
            if(~k)
            {
                k = lst[j][k];
                if(dp[i] < dp[k]+1)
                    dp[i] = dp[k]+1 ,prv[i] = k;
            }
        }
        lst[A[i]].push_back(i);
    }

    int id = max_element(dp.begin() ,dp.end())-dp.begin();
    printf("%d\n",L-dp[id]);

    vector <int> Ans(L ,-1);
    for( ; id >= 0; id = prv[id])
    {
        int p = prv[id];
        if(~p){
            auto t = get_path(p ,id ,id-p+1);
            for(int j=p; j<=id; j++)
                Ans[j] = t[j-p]+1;
        }
    }

    int ln = -1;
    for(int i=0; i<Ans.size(); i++){
        if(~Ans[i])
            ln = Ans[i];
        else if(~ln)
            Ans[i] = ln;
    }
    ln = -1;
    for(int i=Ans.size()-1; ~i; i--){
        if(~Ans[i])
            ln = Ans[i];
        else if(~ln)
            Ans[i] = ln;
    }

    if(ln == -1)
        Ans = vector<int>(L ,A[0]);

    for(int&i : Ans)
        printf("%d ",i);
    printf("\n");
}

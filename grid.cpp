/**
First solution in editorial : https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/Baltic/official/boi2008_solutions/grid-sol-en.pdf
time complexity : O(mCs * n*s * log(4*10^8))
*/

#include <bits/stdc++.h>
using namespace std;

int N ,M ,R ,S;
int C[20][20] ,Su[20][20];
vector <string> Splits;

bool can(int X)
{
    int Sec[S+1] ,Now[S+1];
    for(auto&t : Splits)
    {
        memset(Sec ,0 ,sizeof Sec);
        int Rows = 0;

        for(int r=0; r<N; r++)
        {
            int Ok = 1 ,last = 0;
            for(int i=0; i<S+1; i++){
                Now[i] = Su[r][t[i]+1] - Su[r][last];
                Ok &= (Sec[i]+Now[i] <= X);
                last = t[i]+1;
            }
            if(!Ok){
                memset(Sec ,0 ,sizeof Sec);
                Rows++;
            }
            for(int i=0; i<S+1; i++)
                Sec[i] += Now[i];
            if(*max_element(Sec ,Sec+S+1) > X)
                Rows = 1e9;
        }

        if(Rows <= R)
            return 1;
    }

    return 0;
}

int main()
{
    int ss = 0 ,mm = 0;
    scanf("%d%d%d%d",&N,&M,&R,&S);
    for(int i=0; i<N; i++)
    for(int j=0; j<M; j++)
    {
        scanf("%d",&C[i][j]);
        ss += C[i][j];
        mm = max(mm ,C[i][j]);
        Su[i][j+1] = Su[i][j] + C[i][j];
    }

    queue <string> Next;
    for(int i=0; i<M-S; i++)
        Next.push(string(1 ,i));
    while(!Next.empty())
    {
        auto t = Next.front();  Next.pop();

        if(t.size() == S){
            Splits.push_back(t + char(M-1));
            continue;
        }

        int tt = (M-1)-(S-t.size());
        for(int i=t.back()+1; i<=tt; i++)
            Next.push(t + char(i));
    }

    int st = mm ,en = ss-1 ,mid;
    while(st <= en)
    {
        mid = (st+en)>>1;
        if(can(mid))
            en = mid-1;
        else
            st = mid+1;
    }

    printf("%d\n",en+1);
}

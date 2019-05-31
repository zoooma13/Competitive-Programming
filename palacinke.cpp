/**
same as editorial : https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/COCI/official/2010/contest4_solutions/solutions.pdf
*/

#include <bits/stdc++.h>
using namespace std;

#define matrix vector<vector<int>>
const int mod = 5557;
int GM(int num){
    return (num<0 ? num+mod : num%mod);
}
matrix new_matrix(int n ,int m){
    return matrix(n ,vector<int>(m));
}
matrix operator*(matrix a ,matrix b){
    matrix c = new_matrix(a.size() ,b[0].size());
    for(int i=0; i<a.size(); i++)
    for(int k=0; k<b.size(); k++)
    for(int j=0; j<b[0].size(); j++)
        c[i][j] = GM(c[i][j] + GM(a[i][k]*b[k][j]));
    return c;
}
matrix operator^(matrix a ,int p){
    matrix x = new_matrix(a.size() ,a.size());
    for(int i=0; i<a.size(); i++)
        x[i][i] = 1;
    for( ; p; p>>=1){
        if(p&1)
            x = x*a;
        a = a*a;
    }
    return x;
}

#define MAX_N 25
#define MAX_M 502

int n ,m;
int u[MAX_M] ,v[MAX_M] ,g[MAX_M];
string sh;
int t;
char ing[] = {'P','M','J','B'};

int main()
{
    cin >> n >> m;
    for(int i=0; i<m; i++){
        cin >> u[i] >> v[i] >> sh;
        u[i]-- ,v[i]--;
        for(int b=0; b<4; b++)
            if(find(sh.begin() ,sh.end() ,ing[b]) != sh.end())
                g[i] |= (1<<b);
    }
    cin >> t;t++;

    matrix y = new_matrix(2*n+1 ,1);
    y[0][0] = 1;

    int ans = 0;
    for(int b=0; b<(1<<4); b++){
        matrix x = new_matrix(2*n+1 ,2*n+1);
        for(int i=0; i<m; i++){
            x[v[i]][u[i]] = 1;
            if((b|g[i]) == b)
                x[v[i]][n+u[i]] = 1;
        }
        for(int i=n; i<2*n; i++)
            x[i][i-n] = 1;
        x[2*n][0] = x[2*n][2*n] = 1;

        int inorex = (__builtin_popcount(b)&1 ? -1 : +1);
        ans = GM(ans + ((x^t)*y)[2*n][0]*inorex);
    }

    cout << ans << endl;
}

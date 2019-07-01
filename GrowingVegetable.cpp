/**
https://github.com/nikolapesic2802/Programming-Practice/blob/master/Growing%20vegetable%20is%20fun/main.cpp
*/

#include <bits/stdc++.h>
using namespace std;

#define MAX_N 402
#define INF 0x3f3f3f3f

int n;
string s;
vector <int> pos[3];

int root = -1;
int smlr[3][MAX_N][MAX_N];
vector<vector<vector<int>>> dp[3];
int solve(int t ,int p0 ,int p1 ,int p2){
    if(p0+p1+p2 == n)
		return 0;
    int&ret = (~t ? dp[t][p0][p1][p2] : root);
    if(~ret)
        return ret;
    ret = INF;

    int st[] = {p0 ,p1 ,p2};
    for(int nt=0; nt<3; nt++)
        if(t != nt && st[nt] < pos[nt].size()){
            int cost = 0;
			for(int h=0; h<3; h++) if(h != nt)
				cost += smlr[h][st[h]][pos[nt][st[nt]]];

			st[nt]++;
            ret = min(ret ,cost+solve(nt ,st[0] ,st[1] ,st[2]));
            st[nt]--;
        }
    return ret;
}

int main()
{
    cin >> n;
    cin >> s;

    for(int i=0; i<n; i++){
        if(s[i] == 'R') pos[0].push_back(i);
        if(s[i] == 'G') pos[1].push_back(i);
        if(s[i] == 'Y') pos[2].push_back(i);
    }

    for(int i=0; i<3; i++)
        dp[i].resize(pos[0].size()+1 ,vector<vector<int>>(pos[1].size()+1 ,vector<int>(pos[2].size()+1 ,-1)));

    for(int t=0; t<3; t++)
    for(int i=0; i<pos[t].size(); i++){
        for(int pt_ptr=i ,j=0; j<n; j++){
            while(pt_ptr < pos[t].size() && pos[t][pt_ptr] <= j)
                pt_ptr++;
            smlr[t][i][j] = pt_ptr-i;
        }
    }

    root = -1 ,solve(-1 ,0 ,0 ,0);
    cout << (root == INF ? -1 : root) << endl;
}

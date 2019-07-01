/**
http://usaco.org/current/data/sol_hopscotch_gold.html
*/

#include <bits/stdc++.h>
using namespace std;

#define MAX_N 755

const int mod = 1e9+7;
int GM(int num){
    return (num >= mod ? num-mod : num);
}

struct BIT{
    vector <int> indices ,tree;
    void init(vector<int> ids){
        indices = ids;
        tree.resize(indices.size()+1 ,0);
    }
    void update(int idx ,int val){
        idx = lower_bound(indices.begin() ,indices.end() ,idx)-indices.begin();
        idx = indices.size()-idx;
        for(int i=idx+1; i<tree.size(); i+=(i&-i))
            tree[i] = GM(tree[i]+val);
    }
    int query(int idx){
        idx = lower_bound(indices.begin() ,indices.end() ,idx)-indices.begin();
        idx = indices.size()-idx;
        int ret = 0;
        for(int i=idx+1; i; i-=(i&-i))
            ret = GM(ret+tree[i]);
        return ret;
    }
};

int n ,m ,k;
int g[MAX_N][MAX_N];

unordered_map <int ,BIT> color;
set <int> cols[MAX_N*MAX_N];
int dp[MAX_N][MAX_N];

int main()
{
    freopen("hopscotch.in" ,"r" ,stdin);
    freopen("hopscotch.out" ,"w" ,stdout);

    scanf("%d%d%d",&n,&m,&k);
    for(int i=0; i<n; i++)
    for(int j=0; j<m; j++){
        scanf("%d",&g[i][j]);
        cols[g[i][j]].insert(j);
    }

    for(int i=1; i<=k; i++)
        if(!cols[i].empty())
            color[i].init(vector<int>(cols[i].begin() ,cols[i].end()));

    dp[n-1][m-1] = 1;
    color[g[n-1][m-1]].update(m-1 ,1);

    vector <int> row(m ,1) ,new_row(m ,1);
    for(int i=n-2; ~i; i--){
        for(int j=m-2; ~j; j--)
            dp[i][j] = GM(row[j+1]-color[g[i][j]].query(j+1)+mod);
        for(int j=m-2; ~j; j--){
            color[g[i][j]].update(j ,dp[i][j]);
            new_row[j] = GM(GM(dp[i][j]+new_row[j+1]) + GM(row[j]-row[j+1]+mod));
        }
        swap(row ,new_row);
    }

    printf("%d\n",dp[0][0]);
}

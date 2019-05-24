/**
A visitor coming from entrance 1 can go to entrance :
  2 - if the paths from (bottom to top) & (bottom to right) & (bottom to left) are not blocked
  3 - if the paths from (top to bottom) & (bottom to left) & (left to right) & (right to top) are not blocked
  4 - if the paths from (left to bottom) & (left to top) & (left to right) are not blocked
A path is blocked if a visitor with radius r can't path from one part to another because distance bet. objects is less than his diameter.

We can solve this problem by sorting visitors by their radii in a non-decreasing order
and maintain a sorted list containing distances bet. trees and each other and trees and borders.
distance between a tree and border is the shortest possible distance.

now for every visitor with radius r in sorted visitors :
  +we should block the path between trees with distances < 2*r as the visitor
   can't path through them and so will the visitors after him.
  +check for the possible exiting using the technique mentioned earlier.

tags : union-find ,two pointers
time complexity : O(N^2 * logN)
*/

#include <bits/stdc++.h>
using namespace std;

#define MAX_N 2033
#define MAX_M 100005
#define INF INT_MAX

struct circle{
    int x ,y ,r;
};
struct query{
    int r ,e ,i;
    bool operator<(const query&rhs) const{
        return r < rhs.r;
    }
};
struct line{
    int d ,i ,j;
    bool operator<(const line&rhs) const{
        return d < rhs.d;
    }
};

int n ,m;
int w ,h;
vector <circle> trees;
vector <query> qs;

/**
0 = bottom
1 = right
2 = top
3 = left
*/
int dist_bor(int i ,int b){
    if(b == n+0) return trees[i].y;
    if(b == n+1) return w-trees[i].x;
    if(b == n+2) return h-trees[i].y;
    if(b == n+3) return trees[i].x;
}
int dist_bet(int i ,int j){
    if(i < n && j < n){
        int dx = trees[i].x-trees[j].x ,dy = trees[i].y-trees[j].y;
        return sqrt(1LL*dx*dx+1LL*dy*dy)-trees[i].r-trees[j].r;
    }
    if(i < n && j >= n)
        return dist_bor(i ,j)-trees[i].r;
    if(i >= n && j < n)
        return dist_bor(j ,i)-trees[j].r;
    return INF;
}

int par[MAX_N];
int fnd(int u){
    return par[u] = (par[u]==u ? u : fnd(par[u]));
}
void unn(int u ,int v){
    u = fnd(u) ,v = fnd(v) ,par[u] = v;
}
bool bad(int i ,int j){
    return fnd(n+(i%4)) == fnd(n+(j%4));
}

int main()
{
    iota(par ,par+MAX_N ,0);

    scanf("%d%d",&n,&m); trees.resize(n) ,qs.resize(m);
    scanf("%d%d",&w,&h);
    for(circle&i : trees)
        scanf("%d%d%d",&i.x,&i.y,&i.r);
    int idx = 0;
    for(query&q : qs)
        scanf("%d%d",&q.r,&q.e) ,q.e-- ,q.i = idx++;
    sort(qs.begin() ,qs.end());

    vector <line> evs;
    for(int i=0; i<n+4; i++)
    for(int j=i+1; j<n+4; j++)
        evs.push_back({dist_bet(i ,j) ,i ,j});
    sort(evs.begin() ,evs.end());

    vector<string> ans(m);
    int ev_ptr = 0;
    for(query q : qs){
        while(ev_ptr < evs.size() && evs[ev_ptr].d < 2*q.r)
            unn(evs[ev_ptr].i ,evs[ev_ptr].j) ,ev_ptr++;

        ans[q.i] += char(q.e+'0'+1);
        if(!bad(q.e+0 ,q.e+1) && !bad(q.e+0 ,q.e+2) && !bad(q.e+0 ,q.e+3))
            ans[q.i] += char((q.e+1)%4+'0'+1);
        if(!bad(q.e+0 ,q.e+3) && !bad(q.e+0 ,q.e+2) && !bad(q.e+1 ,q.e+3) && !bad(q.e+1 ,q.e+2))
            ans[q.i] += char((q.e+2)%4+'0'+1);
        if(!bad(q.e+3 ,q.e+0) && !bad(q.e+3 ,q.e+1) && !bad(q.e+3 ,q.e+2))
            ans[q.i] += char((q.e+3)%4+'0'+1);
    }

    for(string&a : ans){
        sort(a.begin() ,a.end());
        printf("%s\n",a.c_str());
    }
}

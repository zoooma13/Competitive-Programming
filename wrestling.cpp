/**
we can solve the problem using sweep line
for every rectangle their are 2 events : 
 1 - the rectangle starts at some x1
 2 - the rectangle ends at some x2
sort events according to x and for each rectangle in sorted list
add +1 to range[y1 ,y2] in DS if it is a starting rectangle or add -1 otherwise
and find the position of maximum element in DS

time complexity : O(N*logN)
*/

#include <bits/stdc++.h>
using namespace std;

#define MAX_N 20004
#define FL (p<<1)|1
#define FR (p<<1)+2

struct rect{
    int x1 ,y1 ,x2 ,y2;
};
struct event{
    int x ,y1 ,y2 ,v;
    bool operator<(const event&rhs) const{
        return (x == rhs.x ? v < rhs.v : x < rhs.x);
    }
};

int t;
int n ,m;
vector <rect> rings;

pair<int ,int> tree[8*MAX_N];
int lazy[8*MAX_N];
void push(int&l ,int&r ,int&p){
    tree[p].first += lazy[p];
    if(l != r){
        lazy[FL] += lazy[p];
        lazy[FR] += lazy[p];
    }lazy[p] = 0;
}
void build(int l=0,int r=2*n ,int p=0){
    lazy[p] = 0;
    if(l == r){
        tree[p] = {0 ,l};
        return;
    }
    int mid = (l+r)>>1;
    build(l ,mid ,FL);
    build(mid+1 ,r ,FR);
    tree[p] = tree[FL];
}
pair<int ,int> upd(int ql ,int qr ,int qv ,int l=0 ,int r=2*n ,int p=0){
    push(l ,r ,p);
    if(ql <= l && r <= qr){
        lazy[p] += qv;
        push(l ,r ,p);
        return tree[p];
    }
    if(qr < l || r < ql)
        return tree[p];

    int mid = (l+r)>>1;
    return tree[p] = max(upd(ql ,qr ,qv ,l ,mid ,FL)
                        ,upd(ql ,qr ,qv ,mid+1 ,r ,FR));
}

int k;
pair <int ,int> ans;
void sweep(){
    vector <event> evs;
    for(rect&r : rings){
        evs.push_back({r.x1 ,r.y1 ,r.y2 ,+1});
        evs.push_back({r.x2+1 ,r.y1 ,r.y2 ,-1});
    }sort(evs.begin() ,evs.end());
    k = 0;
    build();
    for(event&e : evs){
        auto p = upd(e.y1 ,e.y2 ,e.v);
        if(k < p.first){
            k = p.first;
            ans = {e.x ,p.second};
        }
    }
}

int main()
{
    scanf("%d",&t);
    while(t--){
        scanf("%d%d",&n,&m);
        rings.resize(n);
        map <int ,int> mpx ,mpy;
        for(auto&r : rings){
            scanf("%d%d%d%d",&r.x1,&r.y1,&r.x2,&r.y2);
            mpx[r.x1] ,mpx[r.x2];
            mpy[r.y1] ,mpy[r.y2];
            if(r.x1 > r.x2) swap(r.x1 ,r.x2);
            if(r.y1 > r.y2) swap(r.y1 ,r.y2);
        }

        int idx = 0;
        for(auto&p : mpx)
            p.second = idx++;
        idx = 0;
        for(auto&p : mpy)
            p.second = idx++;
        for(auto&r : rings)
            r.x1 = mpx[r.x1] ,r.x2 = mpx[r.x2],
            r.y1 = mpy[r.y1] ,r.y2 = mpy[r.y2];

        sweep();

        for(auto&p : mpx)
            if(p.second == ans.first){
                ans.first = p.first;
                break;
            }
        for(auto&p : mpy)
            if(p.second == ans.second){
                ans.second = p.first;
                break;
            }

        for(int i=1; i<=min(m ,k); i++)
            printf("%d %d\n",ans.first,ans.second);
        for(int i=k+1; i<=m; i++)
            printf("-1 -1\n");
    }
}

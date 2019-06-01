/**
for every node find all its ancestors and add their values to a bitset.
for every two nodes the answr will be the least significant common bit in both bitsets and find its node id.
unfortunately c++ bitset doesn't support finding the least significant bit so we will have to implement it. 

time complexity : O((N^3)/32)
*/

#include <bits/stdc++.h>
using namespace std;

#define MAX_N 3003

const int mod = 666013;

struct bit_ds{
    static const int MAX_MASK_IDX = ((1<<5)-1);
    static inline int lg2(unsigned int num){
        int ret = 0;
        while(num>>=1)ret++;
        return ret;
    }

    unsigned int bits[100] = {0};
    inline void set(int i){i--;
        bits[i>>5] |= (1ul << (i & MAX_MASK_IDX));
    }
    inline int lcb(const bit_ds&rhs){
        for(int i=0; i<100; i++){
            unsigned int bb = (bits[i]&rhs.bits[i]);
            if(bb)
                return (i<<5)+lg2(bb&-bb)+1;
        }
        return 0;
    }
};

int n ,m;
int h[MAX_N] ,ori[MAX_N];
int a ,b;
vector <int> adj[MAX_N];
bit_ds rch[MAX_N];

bool vis[MAX_N];
void bfs(int s){
    memset(vis ,0 ,sizeof vis);
    queue <int> nxt; nxt.push(s);
    while(!nxt.empty()){
        int u = nxt.front(); nxt.pop();
        rch[s].set(h[u]);
        for(int&v : adj[u])
            if(!vis[v])
                nxt.push(v) ,vis[v] = 1;
    }
}

int main()
{
    freopen("casute.in" ,"r" ,stdin);
    freopen("casute.out" ,"w" ,stdout);

    scanf("%d%d",&n,&m);
    for(int i=1; i<=n; i++)
        scanf("%d",&h[i]);

    vector <int> srtd(n);
    iota(srtd.begin() ,srtd.end() ,1);
    sort(srtd.begin() ,srtd.end() ,[](int&i ,int&j){
        return h[i] < h[j];
    });
    for(int i=1; i<=n; i++){
        h[srtd[i-1]] = i;
        ori[i] = srtd[i-1];
    }

    for(int i=0; i<m; i++){
        scanf("%d%d",&a,&b);
        adj[a].push_back(b);
    }
    for(int i=1; i<=n; i++)
        bfs(i);

    int res = 0 ,pow = 1 ,ans;
    for(int i=n; i>0; i--)
    for(int j=n; j>i; j--){
        ans = ori[rch[i].lcb(rch[j])];
        res += (ans*pow)%mod;
        res += (res>=mod ? -mod : 0);
        pow = (pow*(n+1))%mod;
    }

    printf("%d\n",res);
}

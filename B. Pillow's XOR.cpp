#include <bits/stdc++.h>
using namespace std;
 
#define MAX_N 100005
#define INF 0x3f3f3f3f
 
int n ,k;
int a[MAX_N];
 
int ch[3][30*MAX_N] ,nn ,root;
void add(int&p ,int x ,int v ,int i=29)
{
    if(!p)
        p = ++nn;
    if(!~i){
        ch[2][p] = max(ch[2][p] ,v);
        return;
    }
 
    bool zob = x&(1<<i);
    add(ch[zob][p] ,x ,v ,i-1);
    ch[2][p] = max(ch[2][ch[0][p]] ,ch[2][ch[1][p]]);
}
int ask(int&p ,int ai ,int x ,int i=29)
{
    if(!p)
        return -INF;
    if(!~i)
        return ch[2][p];
 
    bool b1 = ai&(1<<i) ,b2 = x&(1<<i);
    if(b1 && b2)
        return ask(ch[0][p] ,ai ,x ,i-1);
    if(b1 && !b2)
        return max(ch[2][ch[0][p]] ,ask(ch[1][p] ,ai ,x ,i-1));
    if(!b1 && b2)
        return ask(ch[1][p] ,ai ,x ,i-1);
    if(!b1 && !b2)
        return max(ch[2][ch[1][p]] ,ask(ch[0][p] ,ai ,x ,i-1));
}
 
bool can(int x)
{
    for(int i=0; i<=nn; i++)
        ch[0][i] = 0 ,ch[1][i] = 0 ,ch[2][i] = -INF;
    root = 0 ,nn = 0;
 
    int bst;
    add(root ,0 ,1);
    for(int i=1; i<=n; i++){
        bst = ask(root ,a[i] ,x);
        add(root ,a[i] ,bst+1);
    }
    return bst >= k;
}
 
int main()
{
    int t;
    scanf("%d",&t);
    while(t--){
        scanf("%d%d",&n,&k);
        for(int i=1; i<=n; i++)
            scanf("%d",&a[i]) ,a[i] ^= a[i-1];
 
        int ans = 0;
        for(int b=29; ~b; b--)
            if(can(ans|(1<<b)))
                ans |= (1<<b);
 
        printf("%d\n",ans);
    }
}

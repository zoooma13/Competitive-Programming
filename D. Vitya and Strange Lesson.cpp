/**
same as editorial : https://codeforces.com/blog/entry/54179
*/

#include <bits/stdc++.h>
using namespace std;

#define MAX_N 300005
#define LOG_N 20

int tr[3][3*MAX_N] ,root ,nn;
void add(int&p ,int x ,int i=LOG_N){
    if(!p) p = ++nn;
    tr[2][p]++;
    if(!~i)  return;
    bool b = x&(1<<i);
    add(tr[b][p] ,x ,i-1);
}
int go(int&p ,int x ,int i=LOG_N){
    if(!p)  return 0;
    if(!~i) return 0;
    bool b = x&(1<<i);
    if(tr[2][tr[b][p]] == (1<<(i)))
        return (1<<i)+go(tr[!b][p] ,x ,i-1);
    else
        return go(tr[b][p] ,x ,i-1);
}

int main()
{
    int n ,q;
    scanf("%d%d",&n,&q);
    set <int> sa;
    for(int a ,i=0; i<n; i++){
        scanf("%d",&a);
        if(sa.find(a) == sa.end())
            add(root ,a);
        sa.insert(a);
    }

    int x ,_x = 0;
    while(q--){
        scanf("%d",&x); _x ^= x;
        printf("%d\n",go(root ,_x));
    }
}

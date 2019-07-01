/**
https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/COCI/COCI-06-Ispiti.txt
*/

#include <bits/stdc++.h>
using namespace std;

#define MAX_N 200005
#define FL (p<<1)|1
#define FR (p<<1)+2

struct query{
    bool t;
    int a ,b ,id;
    query(bool t ,int a ,int b ,int id) : t(t) ,a(a) ,b(b) ,id(id) {}
};

int n;
char c;
int a ,b;
pair <int ,int> stds[MAX_N];
vector <query> qs;

set <pair<int,int>> lf[MAX_N];
int tree[4*MAX_N];

void upd(int id ,int va ,int l=0 ,int r=n ,int p=0){
    if(l == r){
        tree[p] = max(tree[p] ,va);
        return;
    }

    int mid = (l+r)>>1;
    if(id <= mid) upd(id ,va ,l ,mid ,FL);
    else          upd(id ,va ,mid+1 ,r ,FR);
    tree[p] = max(tree[FL] ,tree[FR]);
}
int fnd(int ql ,int qv ,int l=0 ,int r=n ,int p=0){
    if(r < ql)
        return -1;
    if(l == r)
        return (tree[p] >= qv ? l : -1);

    int mid = (l+r)>>1;
    if(ql <= l){
        if(tree[FL] >= qv)
            return fnd(ql ,qv ,l ,mid ,FL);
        if(tree[FR] >= qv)
            return fnd(ql ,qv ,mid+1 ,r ,FR);
        return -1;
    }

    int op1 = fnd(ql ,qv ,l ,mid ,FL);
    return ~op1 ? op1 : fnd(ql ,qv ,mid+1 ,r ,FR);
}

int main()
{
    scanf("%d",&n);
    map<int ,int> mp1 ,mp2;
    for(int add=0 ,i=0; i<n; i++){
        scanf(" %c%d",&c,&a);
        if(c == 'D'){
            scanf("%d",&b);
            swap(a ,b);
            mp1[a] ,mp2[b];
            qs.push_back(query{0 ,a ,b ,++add});
        }else{
            qs.push_back(query{1 ,0 ,0 ,a});
        }
    }

    int idx = 0; for(auto&p : mp1) p.second = ++idx;
    idx = 0;     for(auto&p : mp2) p.second = ++idx;

    for(auto&q : qs){
        q.a = mp1[q.a] ,q.b = mp2[q.b];

        if(!q.t){
            upd(q.a ,q.b);
            stds[q.id] = {q.a ,q.b};
            lf[q.a].insert({q.b ,q.id});
        }else{
            auto it = lf[stds[q.id].first].upper_bound(make_pair(stds[q.id].second ,INT_MAX));
            if(it != lf[stds[q.id].first].end()){
                printf("%d\n",it->second);
                continue;
            }

            int c = fnd(stds[q.id].first+1 ,stds[q.id].second);
            if(~c){
                auto ans = *lf[c].lower_bound(make_pair(stds[q.id].second ,0));
                printf("%d\n",ans.second);
            }
            else
                printf("NE\n");
        }
    }
}

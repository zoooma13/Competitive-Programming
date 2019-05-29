/**
lab a is better to come before b 
 if a.p*b.w < b.p*a.w
and same relation applies to subjects subject a comes before subject b
 if a.total_time*b.total_penalty < b.total_time*a.total_time
*/

#include <bits/stdc++.h>
using namespace std;

#define MAX_N 502

struct lab{
    int w ,p ,idx;
    bool operator<(const lab&rhs) const{
        return rhs.w*p < w*rhs.p;
    }
};
struct subject{
    vector <lab> labs;
    int total_w ,total_t;
    subject(int k){
        labs.resize(k);
        total_w = 0;
        total_t = 0;
    }
    bool operator<(const subject&rhs) const{
        return 1LL*rhs.total_w*total_t < 1LL*total_w*rhs.total_t;
    }
};

int n;
int k[MAX_N];
vector <subject> subs;

int main()
{
    freopen("student.in" ,"r" ,stdin);
    freopen("student.out" ,"w" ,stdout);

    scanf("%d",&n);
    for(int i=0; i<n; i++)
        scanf("%d",&k[i]);
    for(int id=0 ,i=0; i<n; i++){
        subs.push_back(subject(k[i]));
        for(lab&lb : subs[i].labs)
            scanf("%d",&lb.p) ,subs[i].total_t += lb.p ,lb.idx = ++id;
    }
    for(int i=0; i<n; i++){
        for(lab&lb : subs[i].labs)
            scanf("%d",&lb.w) ,subs[i].total_w += lb.w;
    }

    for(int i=0; i<n; i++)
        sort(subs[i].labs.begin() ,subs[i].labs.end());
    sort(subs.begin() ,subs.end());

    long long time = 0 ,penalty = 0;
    vector <int> ans;
    for(int i=0; i<n; i++){
        for(lab&lb : subs[i].labs){
            time += lb.p;
            penalty += lb.w*time;
            ans.push_back(lb.idx);
        }
    }

    printf("%I64d\n",penalty);
    for(int a : ans)
        printf("%d ",a);
    printf("\n");
}

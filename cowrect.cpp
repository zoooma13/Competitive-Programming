/**
http://usaco.org/current/data/sol_cowrect_gold.html
*/

#include <bits/stdc++.h>
using namespace std;

#define point pair<int ,int>
#define x first
#define y second

int n ,a ,b;
char t;
vector <point> good ,bad;

pair <int ,int> mix(pair <int ,int> p1 ,pair <int ,int> p2){
    if(p1.first == p2.first)
        return p1.second < p2.second ? p1 : p2;
    return p1.first > p2.first ? p1 : p2;
}

int main()
{
    freopen("cowrect.in" ,"r" ,stdin);
    freopen("cowrect.out" ,"w" ,stdout);

    scanf("%d",&n);
    vector <int> y_bad{-1 ,1001};
    for(int i=0; i<n; i++){
        scanf("%d%d %c",&a,&b,&t);
        if(t == 'H')
            good.emplace_back(a ,b);
        else
            bad.emplace_back(a ,b) ,y_bad.push_back(b);
    }

    sort(y_bad.begin() ,y_bad.end());
    y_bad.resize(unique(y_bad.begin() ,y_bad.end())-y_bad.begin());

    pair <int ,int> ans = {0 ,0};
    for(int i=0; i<y_bad.size(); i++)
    for(int l=i+1; l<y_bad.size(); l++)
    {
        int y1 = y_bad[i] ,y2 = y_bad[l];

        vector <int> x_bad{-1 ,1001};
        vector <point> now_good;
        for(int j=0; j<bad.size(); j++)
            if(y1 < bad[j].y && bad[j].y < y2)
                x_bad.push_back(bad[j].x);
        for(int j=0; j<good.size(); j++)
            if(y1 < good[j].y && good[j].y < y2)
                now_good.push_back(good[j]);

        sort(now_good.begin() ,now_good.end());
        sort(x_bad.begin() ,x_bad.end());

        int ng_ptr = 0;
        for(int j=0; j<x_bad.size()-1; j++){
            int x1 = x_bad[j] ,x2 = x_bad[j+1];
            while(ng_ptr < now_good.size() && now_good[ng_ptr].x <= x1)
                ng_ptr++;
            if(ng_ptr == now_good.size())
                break;

            int mi_x = now_good[ng_ptr].x ,mx_x ,mi_y = INT_MAX ,mx_y = INT_MIN ,tot_points = 0;
            while(ng_ptr < now_good.size() && now_good[ng_ptr].x < x2){
                mx_x = now_good[ng_ptr].x;
                mi_y = min(mi_y ,now_good[ng_ptr].y);
                mx_y = max(mx_y ,now_good[ng_ptr].y);
                tot_points++;
                ng_ptr++;
            }

            if(tot_points){
                ans = mix(ans ,{tot_points ,(mx_x-mi_x)*(mx_y-mi_y)});
                //cout << tot_points << " in (" << mi_x << " ," << mi_y << ") to (" << mx_x << " ," << mx_y << ")" << endl;
            }
        }
    }

    printf("%d\n",ans.first);
    printf("%d\n",ans.second);
}

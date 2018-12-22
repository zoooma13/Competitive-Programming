/**
editorial : https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/Baltic/official/boi2012_solutions/fire-sol.pdf

regions :
   \  3 | 5  /
   |\---|---/|
   | \ 4|6 / |
 1 |2 \ | / 8| 7
___|___\|/___|___
*/

#include <bits/stdc++.h>
using namespace std;

#define MAX_N 100005

struct Event{
    int id ,x ,re;
    bool operator<(const Event&rhs) const{
        if(x == rhs.x)
            return re > rhs.re;
        return x < rhs.x;
    }
};

int N ,S;
int X[MAX_N] ,Y[MAX_N];

int main()
{
    scanf("%d%d",&N,&S);
    for(int i=0; i<N; i++)
        scanf("%d%d",&Y[i],&X[i]) ,Y[i] = abs(Y[i]);

    vector <Event> evs;
    for(int i=0; i<N; i++){
        if(Y[i] < S){
            evs.push_back({i ,X[i]+S ,1});
            evs.push_back({i ,X[i]+Y[i] ,2});
            evs.push_back({i ,X[i] ,4});
            evs.push_back({i ,X[i]-Y[i] ,6});
            evs.push_back({i ,X[i]-S ,8});
        } else {
            evs.push_back({i ,X[i]+Y[i] ,1});
            evs.push_back({i ,X[i] ,3});
            evs.push_back({i ,X[i]-Y[i] ,5});
        }
    }

    sort(evs.begin() ,evs.end());

    vector <long long> rgX(10) ,rgY(10) ,rgC(10);
    vector <int> currReg(N ,7); //initially all points are in region 7
    for(int i=0; i<N; i++){
        rgX[7] += X[i];
        rgY[7] += Y[i];
    } rgC[7] = N;

    auto Cal = [&](int x){
        return rgY[1]
             + rgY[2] + rgX[2] - rgC[2]*(x-S)
             + rgC[3]*x - rgX[3]
             + rgC[4]*x - rgX[4] + rgC[4]*S - rgY[4]
             + rgX[5] - rgC[5]*x
             + rgX[6] - rgC[6]*x + rgC[6]*S - rgY[6]
             + rgY[7]
             + rgY[8] - rgX[8] + rgC[8]*(x+S);
    };

    long long Ans = rgY[7];
    for(Event ev : evs){
        rgY[currReg[ev.id]] -= Y[ev.id];
        rgX[currReg[ev.id]] -= X[ev.id];
        rgC[currReg[ev.id]]--;
        currReg[ev.id] = ev.re;
        rgY[currReg[ev.id]] += Y[ev.id];
        rgX[currReg[ev.id]] += X[ev.id];
        rgC[currReg[ev.id]]++;

        Ans = min(Ans ,Cal(ev.x));
    }

    cout << Ans << endl;
}

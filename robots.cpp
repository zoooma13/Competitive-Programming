/**
First I solved the simpler subtask with only weak robots using binary search
on time and checking if time is available by assigning the largest possible
number of toys for each toy such that :
    1) weight of the toy < weight limit of the robot
    2) each robot can only carry X toys(the number used by binary search)
these two conditions can be easily checked by two pointers the first pointer
on the robot that we are assigning toys to and second pointer for the heaviest
weight toy less than current robot limit.
finally if no toys are left then time X is available solution.
Time complexity to check if X is available is O(n)
Time complexity of solution O(n*log(T))

then I observed that if there were small robots too then we can make them put away
the left toys but they have size limitation so we need to modify the weak robots such
that they put away the largest size toys with weight less than their limitation
and then put away the left toys by small robots such that the largest robot will remove
the largest X toys and the second largest robot will put away the second largest X toys
ans so on.
if no toys are left then solution time X is available solution.
Time complexity of solution O(n*log(T)*log(n))
*/

#include "robots.h"
#include <bits/stdc++.h>
using namespace std;

#define MAX_T 1000006
#define MAX_A 50004
#define We first
#define Si second

int A ,B ,T;
int Weak[MAX_A];
int Small[MAX_A];
pair <int ,int> WeTs[MAX_T];

bool can(int X)
{
    int Weak_ptr = 0;
    priority_queue <int> pq;

    for(int i=0; i<A; i++)
    {
        while(Weak_ptr < T && WeTs[Weak_ptr].We < Weak[i])
            pq.push(WeTs[Weak_ptr++].Si);

        int CanHave = X;
        while(!pq.empty() && CanHave--)
            pq.pop();
    }

    while(Weak_ptr < T)
        pq.push(WeTs[Weak_ptr++].Si);

    for(int i=B-1; ~i; i--)
    {
        int CanHave = X;
        while(CanHave-- && !pq.empty() && pq.top() < Small[i])
            pq.pop();
    }

    return pq.empty();
}

int putaway(int a, int b, int t, int X[], int Y[], int W[], int S[]) {

    A = a ,B = b ,T = t;
    for(int i=0; i<A; i++)
        Weak[i] = X[i];
    for(int i=0; i<B; i++)
        Small[i] = Y[i];
    for(int i=0; i<T; i++)
        WeTs[i] = {W[i] ,S[i]};

    sort(Weak ,Weak+A);
    sort(Small ,Small+B);
    sort(WeTs ,WeTs+T);

    int st = 1 ,en = T ,mid;
    while(st <= en)
    {
        mid = (st+en)>>1;

        if(can(mid))
            en = mid-1;
        else
            st = mid+1;
    }

    return (en == T ? -1 : en+1);
}

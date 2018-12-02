/**
we need to count number of subarrays with sum >= P*length_of_subarray
S >= P*L
S-P*L >= 0
so we can decrease every element of the array by P and count subarrays with sum >= 0
we can count them by creating cummulative sum array C and for every index i 
count how many elements with index j < i and have C[j] <= C[i]
this can be easily done by ordered set but time limit is strict to pass.
so we can compress values of C and update values in BIT at index C[i] by 1 
*/

#include <bits/stdc++.h>
using namespace std;
 
#define MAX_N 1000006
 
int N;
long long A[MAX_N];
int P;
 
int bit[MAX_N+55];
int query(int idx){
    int ret = 0;
    for(int i=idx+1; i; i-=(i&-i))
        ret += bit[i];
    return ret;
}
void update(int idx){
    for(int i=idx+1; i<=N+5; i+=(i&-i))
        bit[i]++;
}
 
int main()
{
    scanf("%d",&N);
    for(int i=1; i<=N; i++)
        scanf("%lld",&A[i]);
    scanf("%d",&P);
 
    vector <pair<long long ,int>> SA{{0,0}};
    for(int i=1; i<=N; i++){
        A[i] += A[i-1]-P;
        SA.push_back({A[i] ,i});
    }
    sort(SA.begin() ,SA.end());
    for(int i=0; i<=N; i++)
        A[SA[i].second] = i;
 
    long long ans = 0;
    for(int i=0; i<=N; i++){
        ans += query(A[i]);
        update(A[i]);
    }
 
    cout << ans << endl;
}

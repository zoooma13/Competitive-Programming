/**
the problem is basically asking for
  max gcd(a ,b) where S_min <= a <= S_max && W_min <= b <= W_max

we can find the divisors for both ranges and find the maximum common divisor between them.

lets say we want to find all divisors of integers in range [a ,b]
there exists an integer in [a ,b] divisible by integer i iff :
 a + i-(a%i) <= b OR i is a divisor of a
the second case is trivial so lets focus on the first case :
 a + i-(a%i) <= b
 a%i >= a-b+i
 a-(i*floor(a/i)) >= a-b+i
 i*floor(a/i) <= b-i
 i*floor(a/i)+i <= b
 i*(floor(a/i)+1) <= b
we can observe that either i <= sqrt(b) or floor(a/i)+1 <= sqrt(b)
this suggests we check availability of every possible value of i in range [1 ,sqrt(b)]
and check every possible value of floor(a/i)+1 in range [2 ,sqrt(b)]
and the range of i in his case would be (floor(a/m) ,min(a/(m-1) ,b/m)] for m = floor(a/i)+1

now we have 2 sets of ranges where each set contains less than sqrt(b) ranges
and we want to find the maximum common integer among them.

tags : case processing ,sqrt decomposition ,math
time complexity : O(n*sqrt(m))
*/

#include <bits/stdc++.h>
using namespace std;

pair <int ,int> rng_floor(int v ,int n){
    return {n/(v+1)+1 ,n/v};
}

vector <pair<int ,int>> fnd_div(int a ,int b){
    vector <pair<int ,int>> prt1 ,prt3;
    for(int i=1; i*i<=a; i++){
        if(a%i == 0){
            prt1.push_back({i ,i});
            if(i*i != a)
                prt3.push_back({a/i ,a/i});
        }
        else if(i*(a/i+1) <= b)
            prt1.push_back({i ,i});
    }
    reverse(prt3.begin() ,prt3.end());
    prt1.insert(prt1.end() ,prt3.begin() ,prt3.end());

    vector <pair<int ,int>> prt2{{a ,b}};
    for(int di=2; di*di<=b; di++){ ///case where di = 1 is useless because i in that case would be > a
        auto p = rng_floor(di-1 ,a);
        p.second = min(p.second ,b/di);
        if(p.first <= p.second)
            prt2.push_back(p);
    }
    reverse(prt2.begin() ,prt2.end());

    vector <pair<int ,int>> ret;
    merge(prt1.begin() ,prt1.end() ,prt2.begin() ,prt2.end() ,back_inserter(ret));

    vector <pair<int ,int>> good;
    int lst = 1 ,mx = 1;
    for(auto&p : ret){
        if(mx < p.first-1){
            good.push_back({lst ,mx});
            lst = p.first;
        }
        mx = max(mx ,p.second);
    }
    good.push_back({lst ,mx});
    return good;
}

int main()
{
    int n;
    scanf("%d",&n);
    while(n--){
        int a ,b ,c ,d;
        scanf("%d%d%d%d",&a,&b,&c,&d);
        auto rngs1 = fnd_div(a ,b);
        auto rngs2 = fnd_div(c ,d);

        int ans = 1;
        int p2_ptr = 0 ,p1_ptr = 0;
        for(auto&p : rngs1){
            while(p2_ptr < rngs2.size() && rngs2[p2_ptr].second < p.second)
                p2_ptr++;
            if(p2_ptr < rngs2.size())
            if(rngs2[p2_ptr].first <=  p.second && p.second <= rngs2[p2_ptr].second)
                ans = max(ans ,p.second);
        }
        for(auto&p : rngs2){
            while(p1_ptr < rngs1.size() && rngs1[p1_ptr].second < p.second)
                p1_ptr++;
            if(p1_ptr < rngs1.size())
            if(rngs1[p1_ptr].first <=  p.second && p.second <= rngs1[p1_ptr].second)
                ans = max(ans ,p.second);
        }
        printf("%d\n",ans);
    }
}

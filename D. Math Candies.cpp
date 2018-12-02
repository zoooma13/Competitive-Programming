/**
its always better to add digits to the same number than decreasing its size and summing them.
proof : if we have number n and we want to add digit d the profit of doing this = n*10 + d and the number of digits = len(n)+1
        while using sum technique we can get n*2 by using 2*len(n) digits.

so we can simplify the problem to finding the maximum number of length (N-K+1) 
in the string and summing the unused digits to the answer.

this can be done using hashing + binary search in O(N*log(N))
*/

#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

struct PolyHash{
    static const int mod = 1e9+123;
    static vector<int> pow1;
    static vector<ull> pow2;
    static int base;

    vector <int> pref1;
    vector <ull> pref2;

    PolyHash(string&s) : pref1(s.size()+1 ,0) ,pref2(s.size()+1 ,0){
        while(pow1.size() <= s.size())
            pow1.push_back(1LL*pow1.back()*base % mod),
            pow2.push_back(pow2.back()*base);

        for(int i=0; i<s.size(); i++)
            pref1[i+1] = (pref1[i] + 1LL*s[i]*pow1[i]) % mod,
            pref2[i+1] = (pref2[i] + s[i]*pow2[i]);
    }

    inline pair<int ,ull>operator()(int pos ,int len ,int mxpow=0) const{
        int hash1 = pref1[pos+len]-pref1[pos];
        ull hash2 = pref2[pos+len]-pref2[pos];
        hash1 += (hash1 < 0 ? mod : 0);

        if(mxpow != 0)
            hash1 = 1LL*hash1*pow1[mxpow-(pos+len-1)] % mod,
            hash2 *= pow2[mxpow-(pos+len-1)];

        return {hash1 ,hash2};
    }
};

int PolyHash::base(1e9+7);
vector <int> PolyHash::pow1{1};
vector <ull> PolyHash::pow2{1};

int N ,K;
string S;

string sum(string N1 ,string N2)
{
    string Ret = "";

    if(N1.size() < N2.size())
        swap(N1 ,N2);
    N2 = string(N1.size()-N2.size() ,'0') + N2;

    reverse(N1.begin() ,N1.end());
    reverse(N2.begin() ,N2.end());

    bool P = 0;
    for(int i=0; i<N1.size(); i++)
    {
        Ret += (N1[i]+N2[i]+P-96)%10 + '0';
        P = ((N1[i]+N2[i]+P-96) > 9);
    }

    if(P) Ret += '1';
    return string(Ret.rbegin() ,Ret.rend());
}

int main()
{
    cin >> N >> K;
    cin >> S;

    int L = N-(K-1);
    PolyHash hash_s(S);

    vector <int> p(N-L+1 ,0);
    iota(p.begin() ,p.end() ,0);
    auto ans = *max_element(p.begin() ,p.end() ,[&](int i ,int j){
        int st = 1 ,en = L ,mid;
        while(st <= en){
            mid = (st+en)>>1;
            if(hash_s(i ,mid ,N) == hash_s(j ,mid ,N))
                st = mid+1;
            else
                en = mid-1;
        }
        return S[i+st-1] < S[j+st-1];
    });

    int O = 0;
    for(int i=0; i<N; i++)
        if(i < ans || ans+L <= i)
            O += S[i]-'0';

    cout << sum(S.substr(ans ,L) ,to_string(O)) << endl;
}

/**
same editorial idea : https://codeforces.com/blog/entry/59623
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
int PolyHash::base(5);
vector <int> PolyHash::pow1{1};
vector <ull> PolyHash::pow2{1};

int N ,M;
string S;
int X ,Y ,L;

int main()
{
    cin >> N >> M;
    cin >> S;

    for(char&c : S)
        c -= 'a';

    vector <string> cs(26 ,string(N, 1));
    vector <PolyHash> hsh;
    set <int> ss[26];

    for(int i=N-1; ~i; i--){
        cs[S[i]][i] = 2;
        ss[S[i]].insert(i);
    }
    for(int i=0; i<26; i++)
        hsh.push_back(PolyHash(cs[i]));

    while(M--)
    {
        cin >> X >> Y >> L; X-- ,Y--;

        vector <int> bi(26 ,-1);
        bool canbi = 1;

        for(int i=0; i<26; i++)
        {
            auto f = ss[i].lower_bound(Y);
            if(f != ss[i].end() && *f < Y+L)
            {
                int atX = X+(*f-Y);
                if(~bi[S[atX]])
                    canbi = 0;
                else
                    bi[S[atX]] = S[*f];
            }
        }

        if(!canbi){
            cout << "NO" << endl;
            continue;
        }

        bool ans = 1;
        for(int i=0; i<26; i++)
            if(~bi[i])
                ans &= (hsh[bi[i]](Y ,L ,N) == hsh[i](X ,L ,N));

        cout << (ans ? "YES" : "NO") << endl;
    }
}

/**
http://usaco.org/current/data/sol_censor_gold.html
*/

#include <bits/stdc++.h>
using namespace std;

#define MAX_S 100005

const int mod1 = 1e9+7 ,mod2 = 1e9+123;

int base(504);
vector <int> pow1{1} ,pow2{1};
vector <int> inv1{1} ,inv2{1};

pair <int ,int> get_hash(string&s){
    int pref1 = 0 ,pref2 = 0;
    for(int i=0; i<s.size(); i++)
        pref1 = (pref1 + 1LL*s[i]*pow1[i]) % mod1,
        pref2 = (pref2 + 1LL*s[i]*pow2[i]) % mod2;
    return {pref1 ,pref2};
}

int modinv(int a ,int mod){
    int x = 1 ,p = mod-2;
    for( ; p; p>>=1){
        if(p&1)
            x = 1LL*x*a%mod;
        a = 1LL*a*a%mod;
    }
    return x;
}

string s ,a;
int n;
vector <int> lens;
set <pair<int ,int>> bad;

int main()
{
    freopen("censor.in" ,"r" ,stdin);
    freopen("censor.out" ,"w" ,stdout);
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int inv_bs1 = modinv(base ,mod1) ,inv_bs2 = modinv(base ,mod2);
    while(pow1.size() <= MAX_S){
        pow1.push_back(1LL*pow1.back()*base % mod1);
        pow2.push_back(1LL*pow2.back()*base % mod2);
        inv1.push_back(1LL*inv1.back()*inv_bs1 % mod1);
        inv2.push_back(1LL*inv2.back()*inv_bs2 % mod2);
    }

    cin >> s;
    cin >> n;
    for(int i=0; i<n; i++){
        cin >> a;
        lens.push_back(a.size());
        bad.insert(get_hash(a));
        //auto p = get_hash(a);
        //cout << p.first << ' ' << p.second << endl;
    }

    sort(lens.begin() ,lens.end());
    lens.resize(unique(lens.begin() ,lens.end())-lens.begin());

    int i = 1;
    char ans[s.size()+1];
    vector <int> pref1(s.size()+1 ,0);
    vector <int> pref2(s.size()+1 ,0);
    for(char&c : s){
        ans[i-1] = c;
        pref1[i] = (pref1[i-1] + 1LL*c*pow1[i])%mod1;
        pref2[i] = (pref2[i-1] + 1LL*c*pow2[i])%mod2;
        for(int&l : lens){
            if(l > i)
                break;

            int hash1 = pref1[i]-pref1[i-l];
            int hash2 = pref2[i]-pref2[i-l];
            hash1 += (hash1 < 0 ? mod1 : 0);
            hash2 += (hash2 < 0 ? mod2 : 0);
            hash1 = 1LL*hash1*inv1[i-l+1]%mod1;
            hash2 = 1LL*hash2*inv2[i-l+1]%mod2;
            //cout << c << ' ' << hash1 << ' ' << hash2 << endl;

            if(bad.find({hash1 ,hash2}) != bad.end()){
                i -= l;
                break;
            }
        }
        ans[i++] = '\0';
    }

    cout << ans << endl;
}

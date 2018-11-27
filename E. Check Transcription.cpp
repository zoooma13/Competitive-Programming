/**
same editorial idea : https://codeforces.com/blog/entry/63461
*/

#include <bits/stdc++.h>
using namespace std;

#define MAX_N 1000006

vector <int> pow2{1};
vector <int> pref;
int base = 35751;
const int mod = 1e9+123;

int N;
string s;
string t;
int os ,ls ,fo;

int GetHash(int pos ,int len){
    int hsh = pref[pos+len]-pref[pos];
    hsh += (hsh < 0 ? mod : 0);
    hsh = 1LL*hsh*pow2[N-(pos+len-1)] % mod;
    return hsh;
}

bool can(int l1 ,int l2)
{
    int hsh1 = GetHash(0 ,l1) ,hsh2 = GetHash(fo*l1 ,l2);
    if(hsh1 == hsh2)
        return 0;

    for(int i=0 ,p=0; p<s.size(); p++)
    {
        if(s[p] == '0'){
            if(GetHash(i ,l1) != hsh1)
                return 0;
            i += l1;
        }else{
            if(GetHash(i ,l2) != hsh2)
                return 0;
            i += l2;
        }
    }

    return 1;
}

int main()
{
    cin >> s;
    cin >> t;

    N = t.size();
    pref.resize(N+1);
    while(pow2.size() <= N)
        pow2.push_back(1LL*pow2.back()*base % mod);
    for(int i=0; i<N; i++)
        pref[i+1] = (pref[i] + 1LL*t[i]*pow2[i]) % mod;

    if(s[0] == '1')
        for(char&c : s)
            c ^= 1;

    for(int i=s.size()-1; ~i; i--)
    {
        if(s[i] == '1')
            ls++ ,fo = i;
        else
            os++;
    }

    int ans = 0;
    for(int i=1; i*os<N; i++)
        if((N-i*os) % ls == 0)
            ans += can(i ,(N-i*os) / ls);

    cout << ans << endl;
}

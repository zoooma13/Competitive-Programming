/**
same editorial idea : https://codeforces.com/blog/entry/63436
*/

#include <bits/stdc++.h>
using namespace std;

#define MAX_N 255

typedef unsigned long long ull;
int base = MAX_N;
vector<ull> pow2{1};

int N ,M;
vector<short> cu[MAX_N][MAX_N];

pair<ull ,short> diff(vector<short>&x ,vector<short>&y)
{
    ull ret = 0;
    short od = 0;
    for(int i=0; i<26; i++)
    {
        ret = ret + (y[i]-x[i])*pow2[i];
        od += (y[i]-x[i])&1;
    }
    return {ret ,od};
}

int count_pal(vector<ull>&s)
{
    int N = s.size();
    int ret = 0;
    vector<int> d1(N);
    for (int i = 0, l = 0, r = -1; i < N; i++) {
        int k = (i > r) ? 1 : min(d1[l + r - i], r - i);
        while (0 <= i - k && i + k < N && s[i - k] == s[i + k]) {
            k++;
        }
        ret += k;
        d1[i] = k--;
        if (i + k > r) {
            l = i - k;
            r = i + k;
        }
    }
    vector<int> d2(N);
    for (int i = 0, l = 0, r = -1; i < N; i++) {
        int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
        while (0 <= i - k - 1 && i + k < N && s[i - k - 1] == s[i + k]) {
            k++;
        }
        ret += k;
        d2[i] = k--;
        if (i + k > r) {
            l = i - k - 1;
            r = i + k ;
        }
    }
    return ret;
}

int main()
{
    while(pow2.size() <= MAX_N)
        pow2.push_back(pow2.back()*base);

    cin >> N >> M;
    for(int i=0; i<N; i++)
    {
        string S;
        cin >> S;
        
        cu[i][0] = vector<short>(26 ,0);
        for(int j=0; j<M; j++){
            cu[i][j+1] = cu[i][j];
            cu[i][j+1][S[j]-'a']++;
        }
    }

    int Ans = 0;
    for(int i=0; i<M; i++)
    for(int j=i; j<M; j++)
    {
        vector<ull> sij;

        for(int l=0; l<N; l++)
        {
            auto t = diff(cu[l][i] ,cu[l][j+1]);

            if(t.second <= 1)
                sij.push_back(t.first);
            else{
                Ans += count_pal(sij);
                sij.clear();
            }
        }

        Ans += count_pal(sij);
    }

    cout << Ans << endl;
}

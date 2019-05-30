/**
same as editorial : https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/COCI/official/2017/contest4_solutions/solutions.pdf
*/

#include <bits/stdc++.h>
using namespace std;

#define MAX_N 500005
#define MAX_S 3000006

int n;
string s;

int root ,nn;
int tr[27][MAX_S];
void add(int&p ,int i=0){
    if(!p) p = ++nn;
    if(i == s.size()){
        tr[26][p]++;
        return;
    }
    add(tr[s[i]-'a'][p] ,i+1);
}
int max_suf = 0;
int dfs(int&p){
    int ch ,frst_mx_ch = 0 ,scnd_mx_ch = 0 ,all_en = 0;
    for(int c=0; c<26; c++) if(tr[c][p])
    {
        ch = dfs(tr[c][p]);
        all_en += tr[26][tr[c][p]];
        if(tr[26][tr[c][p]])
        {
            if(frst_mx_ch < ch){
                scnd_mx_ch = frst_mx_ch;
                frst_mx_ch = ch;
            }
            else if(scnd_mx_ch < ch){
                scnd_mx_ch = ch;
            }
        }
    }
    max_suf = max(max_suf ,frst_mx_ch+scnd_mx_ch+all_en+tr[26][p]);
    return frst_mx_ch+all_en;
}

int main()
{
    cin >> n;
    for(int i=0; i<n; i++){
        cin >> s; reverse(s.begin() ,s.end());
        add(root);
    }

    dfs(root);
    cout << max_suf << endl;
}

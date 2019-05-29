/**
the idea is quite simple you can sole it using a trie or hashing but trie memory complexity is hard to optimize.
sort the queries according to their occurence in dictionary if it doesn't exist in dictionary its occ = n.
maintain two pointers on current query and the other on the last word added.
then add all words with indices less than curr query to a trie or do a hash for all its prefixes.
then answer queries offline for every prefix of query string count number of prefices that are added before. 

memory optimizations :
use char* instead of string
don't use map all the time once map size > 20000 insert its elements into sorted vector and binary search on it instead and clear the map
*/

#include <bits/stdc++.h>
using namespace std;

#define MAX_N 30004

short n ,q;
char s[2*MAX_N][31];
vector <pair <char* ,short>> occ;

vector <pair<pair<pair<int ,int> ,char>,short>> prfx;
const int mod1 = 1e9+123 ,mod2 = 1e9+7;
int hsh1 ,hsh2;
int pow1 ,pow2;
pair<pair<int ,int> ,char> gethash(char*s ,int&j){
    hsh1 = 0 ,hsh2 = 0;
    pow1 = 1 ,pow2 = 1;
    for(int i=0; i<j; i++){
        hsh1 = (hsh1 + 1LL*(s[i]-'a')*pow1)%mod1;
        hsh2 = (hsh2 + 1LL*(s[i]-'a')*pow2)%mod2;
        pow1 = (pow1*27LL)%mod1;
        pow2 = (pow2*27LL)%mod2;
    }
    return {{hsh1 ,hsh2} ,j};
}

map <pair<pair<int ,int> ,char>,short> temp;
vector <pair<pair<pair<int ,int> ,char>,short>>::iterator iti;
void add(pair<pair<int ,int> ,char>hsh){
    iti = lower_bound(prfx.begin() ,prfx.end() ,make_pair(hsh ,0) ,[](auto&i ,auto&j){
        return i.first == j.first ? i.second < j.second : i.first < j.first;
    });
    if(iti==prfx.end() || iti->first != hsh)
        temp[hsh]++;
    else
        iti->second++;

    if(temp.size()>20000){
        for(auto&p : temp)
            prfx.push_back(p);
        temp.clear();
        sort(prfx.begin() ,prfx.end() ,[](auto&i ,auto&j){
            return i.first == j.first ? i.second < j.second : i.first < j.first;
        });
    }
}
short get(pair<pair<int ,int> ,char>hsh){
    iti = lower_bound(prfx.begin() ,prfx.end() ,make_pair(hsh ,0) ,[](auto&i ,auto&j){
        return i.first == j.first ? i.second < j.second : i.first < j.first;
    });
    if(iti!=prfx.end() && iti->first == hsh)
        return iti->second;
    if(temp.find(hsh) == temp.end())
        return 0;
    return temp[hsh];
}

int main()
{
    int i , j ,sm ,len;
    pair<pair<int ,int> ,char>  hsh;
    vector<pair <char* ,short>>::iterator it;

    cin >> n;
    for(i=0; i<n; i++){
        cin >> s[i];
        occ.push_back({s[i] ,i+1});
    }
    sort(occ.begin() ,occ.end() ,[](auto&i ,auto&j){
        return strcmp(i.first ,j.first) < 0;
    });

    vector <pair<pair<short ,char*> ,short>> qs;
    cin >> q;
    for(sm,i=0; i<q; i++){
        cin >> s[n+i];
        it = lower_bound(occ.begin() ,occ.end() ,make_pair(s[n+i] ,0),[](auto&i ,auto&j){
            return strcmp(i.first ,j.first) < 0;
        });
        sm = n;
        if(it!=occ.end() && strcmp(it->first ,s[n+i]) == 0)
            sm = it->second;
        qs.push_back({{sm ,s[n+i]} ,i});
    }

    sort(occ.begin() ,occ.end() ,[](auto&i ,auto&j){
        return i.second < j.second;
    });
    sort(qs.begin() ,qs.end() ,[](auto&i ,auto&j){
        return i.first.first < j.first.first;
    });

    vector <int> ans(q);
    short occ_ptr = 0;
    for(auto&q : qs){
        while(occ_ptr < q.first.first){
            len = strlen(occ[occ_ptr].first);
            for(j=1; j<=len; j++)
                add(gethash(occ[occ_ptr].first ,j));
            occ_ptr++;
        }
        ans[q.second] = q.first.first;

        len = strlen(q.first.second);
        for(j=1; j<=len; j++){
            hsh = gethash(q.first.second ,j);
            sm = get(hsh);
            if(!sm)
                break;
            ans[q.second] += sm;
        }
    }

    for(int&i : ans)
        cout << i << endl;
}

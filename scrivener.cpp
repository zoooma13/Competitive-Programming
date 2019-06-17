/**
tags : tree ,binary lifting
time complexity O(q*logn)
*/

#include <bits/stdc++.h>
using namespace std;

#define MAX_COMM 1000006
#define LOG_COMM 20

int curr_comm;
char edg_char[MAX_COMM];
int par[MAX_COMM][LOG_COMM] ,dist[MAX_COMM][LOG_COMM];
int dist_root[MAX_COMM];

void bld_anc(int u ,int p ,int v){
    par[u][0] = p;
    dist[u][0] = (bool)v;
    dist_root[u] = dist_root[p]+(bool)v;
    edg_char[u] = (v ? v : edg_char[p]);
    for(int i=1; i<LOG_COMM; i++)
        if(~par[u][i-1]){
            par[u][i] = par[par[u][i-1]][i-1];
            dist[u][i] = dist[u][i-1] + dist[par[u][i-1]][i-1];
        }
}

void Init(){
    curr_comm = 0;
    memset(par ,-1 ,sizeof par);
    memset(dist ,0 ,sizeof dist);
    memset(dist_root ,0 ,sizeof dist_root);
}
void TypeLetter(char L){++curr_comm;
    bld_anc(curr_comm ,curr_comm-1 ,L);
}
void UndoCommands(int U){++curr_comm;
    bld_anc(curr_comm ,curr_comm-U-1 ,0);
}

char GetLetter(int P){
    int u = curr_comm;
    P = dist_root[u]-P-1;
    for(int i=LOG_COMM-1; ~i; i--)
        if(~par[u][i] && dist[u][i] <= P){
            P -= dist[u][i];
            u = par[u][i];
        }
    return edg_char[u];
}

int main() {
  Init();

  int cmd_num;
  int tmp = scanf("%d", &cmd_num);
  assert(tmp == 1);

  int i;
  for (i = 0; i < cmd_num; i++) {
    char cmd;
    tmp = scanf(" %c", &cmd);
    assert(tmp == 1);
    if (cmd == 'T') {
      char letter;
      tmp = scanf(" %c", &letter);
      assert(tmp == 1);
      TypeLetter(letter);
    }
    else if (cmd == 'U') {
      int number;
      tmp = scanf("%d", &number);
      assert(tmp == 1);
      UndoCommands(number);
    }
    else if (cmd == 'P') {
      int index;
      char letter;
      tmp = scanf("%d", &index);
      assert(tmp == 1);
      letter = GetLetter(index);
      printf("%c\n", letter);
    }
  }

  return 0;
}

/* Author : arman_ferdous 
 * Date   : 28 Apr 2020 14:31:14
 * Idea   : Use euler tour to find edge-disjoint cycles. For 100pts use better graph representation. 
 */

#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,avx2,fma")

using ll = long long;
using ii = pair<int,int>;

const int N = 5e5+10;
const int M = 1e6+10;

int n, m;
int eptr, to[M], pre[M], last[M];

void add_edge(int u, int v) {
  to[eptr] = v;
  pre[eptr] = last[u];
  last[u] = eptr;
  eptr++;
}

int vis[M];
int st[M], ptr;
void tour(int u) {
  for(int i = last[u]; i + 1; i = last[u]) {
    last[u] = pre[i];
    if(vis[i]) continue;
    vis[i] = 1;
    vis[i ^ 1] = 1;
    tour(to[i]);
  }
  st[ptr++] = u;
}

stack<int> soln;
int main() { 
  scanf("%d %d", &n, &m);
  for(int i = 0; i < m + m; i++) last[i] = -1;
  for(int i = 0; i < m; i++) {
    int u, v; scanf("%d %d", &u, &v);
    add_edge(u, v);
    add_edge(v, u);
  }
  tour(1); ptr--;
  for(int i = 1; i <= n; i++) vis[i] = 0;
  while(ptr >= 0) {
    int u = st[ptr--];
    if(vis[u]) {
      printf("%d ", u);
      while(!soln.empty()) {
        int v = soln.top(); soln.pop();
        if(v == u) break;
        printf("%d ", v);
        vis[v] = 0;
      }
      puts("");
    } 
    vis[u] = 1;
    soln.push(u);
  }
  return 0;
}

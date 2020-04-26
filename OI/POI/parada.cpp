/* Author : arman_ferdous 
 * Date   : 25 Apr 2020 15:24:06
 * Idea   : Problem can be converted in to finding diameter of a tree 
 */

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ii = pair<int,int>;

const int N = 2e5+10;
int n, deg[N];
vector<int> g[N];

int dist[N];
void dfs(int u, int f) {
  dist[u] = dist[f] + deg[u];
  for(int v : g[u]) 
    if(v != f) 
      dfs(v, u);
}
int main() { 
  scanf("%d", &n);
  for(int i = 1; i < n; i++) {
    int u, v; scanf("%d %d", &u, &v);
    g[u].push_back(v);
    g[v].push_back(u);
    deg[u]++, deg[v]++;
  }
  for(int i = 1; i <= n; i++) deg[i] -= 2;
  dfs(1, 0);
  int mx = -N, p;
  for(int i = 1; i <= n; i++) if(i != 1 && dist[i] > mx)
    mx = dist[i], p = i;
  dfs(p, 0); mx = -N;
  for(int i = 1; i <= n; i++) if(i != p) 
    mx = max(mx, dist[i]);
  printf("%d\n", mx + 2);
  return 0;
}

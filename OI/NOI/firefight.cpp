/* Author : arman_ferdous 
 * Date   : 22 Apr 2020 20:50:17
 * Crux   : Greedily go up as long as possible without putting stations.
 */

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ii = pair<int,int>;

const int N = 3e5+10;
const ll oo = 1e18;

int n, fire[N]; ll k;
vector<pair<ll, int>> g[N];

struct data { 
  int ty;
  ll x, w;
}dp[N];

void solve(int u, int f, ll up) {
  int cnt = 0, over = 0, under = 0;
  for(auto e : g[u]) if(e.second != f) {
    int &v = e.second;
    solve(v, u, e.first);
    if(dp[v].ty == 0) under++;
    else over++;
    cnt++;
  }
  if(cnt == 0) {
    if(up <= k) dp[u] = {0, 0, up};
    else dp[u] = {0, 1, 0}, fire[u] = 1;
    return;
  }
  ll overflow = -oo, underflow = 0, x = 0;
  for(auto e : g[u]) if(e.second != f) {
    int &v = e.second;
    if(dp[v].ty == 0) {
      underflow = max(underflow, dp[v].w);
      x += dp[v].x;
    }
    else {
      overflow = max(overflow, dp[v].w);
      x += dp[v].x;
    }
  }
  if(overflow >= underflow) {
    if(overflow - up >= 0) dp[u] = {1, x, overflow - up}; 
    else dp[u] = {0, x, 0}; 
  } else {
    if(up + underflow <= k) dp[u] = {0, x, up + underflow};
    else {
      fire[u] = 1;
      if(k - up >= 0) dp[u] = {1, x + 1, k - up};
      else dp[u] = {0, x + 1, 0};
    }
  }
  return;
}

int main() { 
  scanf("%d %lld", &n, &k);
  for(int i = 1; i < n; i++) {
    int u, v, c; scanf("%d %d %d", &u, &v, &c);
    g[u].push_back({c, v});
    g[v].push_back({c, u});
  }
  solve(1, -1, oo);
  printf("%lld\n", dp[1].x);
  for(int i = 1; i <= n; i++) if(fire[i]) printf("%d ", i); 
  puts("");
  return 0;
}

/* Author : arman_ferdous 
 * Date   : 21 Apr 2020 16:03:47
 * TAG    : Dijkstra 
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long
using ll = long long;
using ii = pair<ll,int>;
const int N = 10010;
const int M = 50010;
const int oo = 2e9;

int n, m, s, t, p;
vector<int> g[N], tra[N];
int l[M], r[M], w[M];
ll dist1[N], dist2[N];

priority_queue<ii, vector<ii>, greater<ii>> q;
int32_t main() { 
  int T, cs = 1;
  scanf("%lld", &T);
  while(T--) {
    scanf("%lld %lld %lld %lld %lld", &n, &m, &s, &t, &p);
    for(int i = 0; i < m; i++) {
      scanf("%lld %lld %lld", &l[i], &r[i], &w[i]);
      g[l[i]].push_back(i);
      tra[r[i]].push_back(i);
    }
    
    for(int i = 1; i <= n; i++) 
      dist1[i] = dist2[i] = oo;
    q.push({0, s});
    dist1[s] = 0;
    while(!q.empty()) {
      int u = q.top().second, cw = q.top().first; q.pop();
      for(int e : g[u]) {
        int v = u ^ l[e] ^ r[e];
        if(dist1[v] > cw + w[e]) {
          dist1[v] = cw + w[e];
          q.push({cw + w[e], v});
        }
      }
    }
    q.push({0, t});
    dist2[t] = 0;
    while(!q.empty()) {
      int u = q.top().second, cw = q.top().first; q.pop();
      for(int e : tra[u]) {
        int v = u ^ l[e] ^ r[e];
        if(dist2[v] > cw + w[e]) {
          dist2[v] = cw + w[e];
          q.push({cw + w[e], v});
        }
      }
    }
    int ans = -1;
    for(int i = 0; i < m; i++) {
      if(dist1[l[i]] < oo && dist2[r[i]] < oo && dist1[l[i]] + w[i] + dist2[r[i]] <= p) {
        ans = max(ans, w[i]);
      }
    }
    printf("Case %lld: %lld\n", cs++, ans);
    for(int i = 1; i <= n; i++) g[i].clear(), tra[i].clear();
  }
  return 0;
}

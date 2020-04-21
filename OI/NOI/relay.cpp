#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ii = pair<ll,int>;
const int N = 1e5+10;
const int M = 3e6+10;
const ll oo = 1e16;

int n, m, k;
int a[N];
vector<ii> g[N];

int head[N];
ll dist[N];

struct edge{
  int u, v; ll w;
}E[M];

priority_queue<ii, vector<ii>, greater<ii>> q;

ll solve1(int x1, int y1) {
  for(int i = 1; i <= n; i++) 
    dist[i] = oo, head[i] = -1;
  for(int i = 0; i < k; i++) {
    if(a[i] == x1 || a[i] == y1) continue;
    q.push({0, a[i]});
    dist[a[i]] = 0;
    head[a[i]] = a[i];
  }
  while(!q.empty()) {
    auto it = q.top(); q.pop();
    int u = it.second; ll cw = it.first;
    if(dist[u] < cw) continue;
    for(auto e : g[u]) {
      if(dist[e.second] > cw + e.first) {
        dist[e.second] = cw + e.first;
        head[e.second] = head[u];
        q.push({cw + e.first, e.second});
      }
    }
  }
  int p, q; ll mn = oo;
  for(int i = 0; i < m; i++) {
    if(head[E[i].u] == -1 || head[E[i].v] == -1) continue;
    if(head[E[i].u] != head[E[i].v] && mn > dist[E[i].u] + E[i].w + dist[E[i].v]) {
      mn = dist[E[i].u] + E[i].w + dist[E[i].v];
      p = head[E[i].u], q = head[E[i].v];
    }
  }
  return mn;
}

ll solve2(int x1, int x2) {
  for(int i = 1; i <= n; i++) dist[i] = oo;
  q.push({0, x1});
  while(!q.empty()) {
    auto it = q.top(); q.pop();
    int u = it.second; ll cw = it.first;
    for(auto e : g[u]) if(dist[e.second] > e.first + cw) {
      dist[e.second] = e.first + cw;
      q.push({e.first + cw, e.second});
    }
  }
  vector<ii> v1, v2;
  for(int i = 0; i < k; i++) if(a[i] != x1 && a[i] != x2) {
    v1.push_back({dist[a[i]], a[i]});
    sort(v1.begin(), v1.end());
    if((int)v1.size() > 2) v1.pop_back();
  }
  for(int i = 1; i <= n; i++) dist[i] = oo;
  q.push({0, x2});
  while(!q.empty()) {
    auto it = q.top(); q.pop();
    int u = it.second; ll cw = it.first;
    for(auto e : g[u]) if(dist[e.second] > e.first + cw) {
      dist[e.second] = e.first + cw;
      q.push({e.first + cw, e.second});
    }
  }
  for(int i = 0; i < k; i++) if(a[i] != x1 && a[i] != x2) {
    v2.push_back({dist[a[i]], a[i]});
    sort(v2.begin(), v2.end());
    if((int)v2.size() > 2) v2.pop_back();
  }
  ll ret = oo;
  for(auto y1 : v1) for(auto y2 : v2) {
    if(y1.second != y2.second)
      ret = min(ret, y1.first + y2.first);
  }
  return ret;
}

int main() {
  scanf("%d %d %d", &n, &m, &k);
  assert(n <= N); assert(k <= N);
  for(int i = 0; i < m; i++) {
    scanf("%d %d %lld", &E[i].u, &E[i].v, &E[i].w);
    g[E[i].u].emplace_back(E[i].w, E[i].v);
    g[E[i].v].emplace_back(E[i].w, E[i].u);
  }
  for(int i = 0; i < k; i++) scanf("%d", &a[i]);
  
  for(int i = 1; i <= n; i++) dist[i] = oo, head[i] = -1;
  for(int i = 0; i < k; i++) {
    q.push({0, a[i]});
    dist[a[i]] = 0;
    head[a[i]] = a[i];
  }
  while(!q.empty()) {
    auto it = q.top(); q.pop();
    int u = it.second; ll cw = it.first; 
    if(dist[u] < cw) continue;
    for(auto e : g[u]) {
      if(dist[e.second] > cw + e.first) {
        dist[e.second] = cw + e.first;
        head[e.second] = head[u];
        q.push({cw + e.first, e.second});
      }
    }
  }
  int x1, y1; ll mn = oo;
  for(int i = 0; i < m; i++) {
    if(head[E[i].u] + 1 && head[E[i].v] + 1 && head[E[i].u] != head[E[i].v] && mn > dist[E[i].u] + E[i].w + dist[E[i].v]) {
      mn = dist[E[i].u] + E[i].w + dist[E[i].v];
      x1 = head[E[i].u], y1 = head[E[i].v];
    }
  }
  ll ans = min(solve1(x1, y1) + mn, solve2(x1, y1));
  printf("%lld\n", ans);
  return 0;
}

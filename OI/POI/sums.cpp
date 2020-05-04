/* Author : arman_ferdous 
 * Date   : 04 May 2020 14:14:39
 * TAG    : Modular dijkstra 
 */

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ii = pair<ll,int>;

const int N = 5010;
const int M = 50010;
const ll oo = INT_MAX;

int n, m, a[N], b[N];
int dist[M], inQ[M];
queue<int> q;

int main() { 
  scanf("%d", &n);
  for(int i = 0; i < n; i++)
    scanf("%d", &a[i]);
  sort(a, a + n);

  for(int i = 0; i < n; i++) b[i] = a[i] % a[0];
  
  for(int i = 0; i < a[0]; i++)
    dist[i] = oo;
  dist[0] = 0;

  q.push(0);
  inQ[0] = 1;
  while(!q.empty()) {
    int u = q.front();
    q.pop();
    inQ[u] ^= 1;
    for(int i = 1; i < n; i++) {
      int v = u + b[i];
      if(v >= a[0]) v -= a[0];
      if(dist[v] > dist[u] + a[i]) {
        dist[v] = dist[u] + a[i];
        if(!inQ[v]) q.push(v);
        inQ[v] ^= 1;
      }
    }
  }
  scanf("%d", &m);
  while(m--) {
    int x; scanf("%d", &x);
    if(dist[x % a[0]] <= x) puts("TAK");
    else puts("NIE");
  }
  return 0;
}

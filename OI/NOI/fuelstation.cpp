/* Author : arman_ferdous 
 * Date   : 23 Apr 2020 01:07:58
 * TAG    : Data Structres 
 */

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ii = pair<int,int>;

const int N = 3e5+10;
const ll oo = 1e18;

int n; ll d;
struct DATA{
  ll x, a, b, id;
}a[N];

ll tmp[N];
ll t[N << 2], lazy[N << 2];

void build(int node, int L, int R) {
  if(L == R) {
    t[node] = tmp[L];
    return;
  } int mid = L + R >> 1, lc = node << 1, rc = lc | 1;
  build(lc, L, mid); build(rc, mid + 1, R);
  t[node] = min(t[lc], t[rc]);
}

void shift(int node, int L, int R) {
  int lc = node << 1, rc = lc | 1;
  t[lc] += lazy[node];
  t[rc] += lazy[node];
  lazy[lc] += lazy[node];
  lazy[rc] += lazy[node];
  lazy[node] = 0;
}

void upd(int node, int L, int R, int l, int r, ll x) {
  if(r < L || R < l || r < l) return;
  if(l <= L && R <= r) {
    t[node] += x;
    lazy[node] += x;
    return;
  } 
  if(lazy[node] != 0) shift(node, L, R);
  int mid = L + R >> 1, lc = node << 1, rc = lc | 1;
  upd(lc, L, mid, l, r, x); upd(rc, mid + 1, R, l, r, x);
  t[node] = min(t[lc], t[rc]);
}

ll get() {
  return t[1];
}

int main() { 
  scanf("%d %lld", &n, &d);
  for(int i = 0; i < n; i++) 
    scanf("%lld %lld %lld", &a[i].x, &a[i].a, &a[i].b);
  a[n].x = d, a[n].a = 0, a[n].b = oo; n++;
  sort(a, a + n, [&](DATA &i, DATA &j){
    return i.x < j.x;
  });
  for(int i = 0; i < n; i++) a[i].id = i;
  for(int i = 0; i < n; i++) tmp[i] = -a[i].x;
  build(1, 0, n - 1);

  sort(a, a + n, [&](DATA &i, DATA &j) {
    return i.b > j.b;
  });

  ll ans = -get();
  for(int i = 0; i < n; ) {
    int j = i;
    while(j + 1 < n && a[j + 1].b == a[i].b) j++;
    while(i <= j) {
      upd(1, 0, n - 1, a[i].id + 1, n - 1, a[i].a); 
      i++;
    }
    ll mn = get();
    if(-mn <= a[i - 1].b) ans = min(ans, -mn);
  }
  printf("%lld\n", ans);
  return 0;
}

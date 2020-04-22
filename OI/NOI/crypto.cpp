#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int N = 3e5+10;
const int MOD = 1000000007;
int n, a[N];

vector<int> v;
map<int,int> mp; 

int bit[N];
void upd(int pos, int x) {
  while(pos < N) bit[pos] += x, pos += pos&-pos;
}
int get(int pos, int r = 0) {
  while(pos > 0) r += bit[pos], pos -= pos&-pos;
  return r;
}

ll f[N];

int main () {
  f[0] = 1;
  for(ll i = 1; i < N; i++)
    f[i] = f[i - 1] * i % MOD;

  scanf("%d", &n);
  for(int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    v.push_back(a[i]);
  }
  sort(v.begin(), v.end());
  v.erase(unique(v.begin(), v.end()), v.end());
  int cur = 1;
  for(int x : v) mp[x] = cur++;
  for(int i = 1; i <= n; i++) {
    a[i] = mp[a[i]];
    upd(i, 1);
  }

  ll ans = 1;
  for(int i = 1; i < n; i++) {
    ll x = get(a[i] - 1);
    ll y = f[n - i];
    ans += x * y % MOD;
    if(ans >= MOD) ans -= MOD;
    upd(a[i], -1);
  }
  printf("%lld\n", ans);
  return 0;
}
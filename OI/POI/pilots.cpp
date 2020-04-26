/* Author : arman_ferdous 
 * Date   : 25 Apr 2020 14:01:34
 * TAG    : Noob Problem 
 */

#include <bits/stdc++.h>
using namespace std;
#define int unsigned int
using ll = long long;
using ii = pair<int,int>;

const int N = 3e6+2;
int n, d, a[N];
multiset<int> st;

int32_t main() { 
  scanf("%u %u", &d, &n);
  for(int i = 0; i < n; i++)
    scanf("%u", &a[i]);
  int l = 0, ans = 0, mn, mx; 
  for(int i = 0; i < n; i++) {
    st.insert(a[i]);
    mn = *st.begin();
    mx = *st.rbegin();
    while(mx - mn > d) {
      st.erase(st.find(a[l++]));
      if(a[l - 1] == mn) mn = *st.begin();
      else if(a[l - 1] == mx) mx = *st.rbegin();
    }
    ans = max(ans, i - l + 1);
  } printf("%u\n", ans);
  return 0;
}

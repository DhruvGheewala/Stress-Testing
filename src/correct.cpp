/**
  *  Author: dhruv_gheewala
  *  Problem: Equal Beauty
  *  Date:   23.10.2021
  *  Time:   13:15:55
**/

#include "bits/stdc++.h"
using namespace std;

#ifndef DEBUG

#define fundri 108
#define debug(...) 1729
#define endl '\n'

#endif

#define int int64_t

typedef pair<int, int> pii;
typedef vector<int> vi;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
inline int rnd(int l = 0, int r = INT_MAX) {return uniform_int_distribution<int>(l, r)(rng);}

bool in_range(int x, int l, int r) {return l <= x && x <= r;}
template<typename H, typename ...T>void inp(H &head) {cin >> head;}
template<typename H, typename ...T>void inp(H &head, T &...tail) {cin >> head;inp(tail...);}
template<typename T>inline istream &operator >>(istream &in, vector<T> &a) {for(T &x : a)in >> x; return in;}
template<typename T, typename U>inline istream &operator >>(istream &in, pair<T, U> &a) {in >> a.first >> a.second; return in;}

// Multi-Dimension Vector
// Usage: vec<n, data-type> dp(dimention-1, dimention-2, ..., dimention-n, default = data-type())
template<int D, typename T> struct vec : public vector<vec<D - 1, T>> {
    static_assert(D >= 1, "Vector dimensions must be greater than zero !!");
    template<typename... Args>
    vec(int n = 0, Args... args) : vector<vec<D - 1, T>>(n, vec<D - 1, T>(args...)){}
};

template<typename T> struct vec<1, T> : public vector<T> {vec(int n = 0, T val = T()) : vector<T>(n, val){}};

const int inf = 1e15;
const bool testcases = true;

const bool ready = []() -> bool {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

#ifdef DHRUV_GHEEWALA
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
	freopen("debug.txt", "w", stderr);
#endif

    return true;
}();

void solve(int tc);
int32_t main(int32_t argc, char **argv) {
    int TC = 1;
    if(testcases) cin >> TC;

    // Pre-Processing goes here...
    for(int tc = 1; tc <= TC; ++tc) {
        solve(tc);
        fundri;
    }
    exit(0);
}

void optimal(int n, vector<int> &a) {
	sort(a.begin(), a.end());

    int ans = inf;
    for(int i = 1; i < n; i++) {
    	int left_diff = a[i - 1] - a[0];
    	int right_diff = a[n - 1] - a[i];
    	ans = min(ans, abs(right_diff - left_diff));

    	if(right_diff == left_diff) {
    		cout << 0 << endl;
    		return;
    	}

    	if(left_diff < right_diff) {
    		// we have to increase the max of left part
    		// or increase the min of right part <== this is not possible

    		// right_diff <= (a[ind] - a[0])
    		// a[ind] >= right_diff + a[0]
    		// but, ind: [i + 1, n - 2]

    		int ind = upper_bound(a.begin() + i + 1, a.begin() + n - 1, right_diff + a[0]) - a.begin();
    		for(int rep = 0; rep < 3; rep++) {
	    		if(in_range(ind - rep, i + 1, n - 2))
	    			ans = min(ans, abs(right_diff - (a[ind - rep] - a[0])));
    		}
    	} else {
    		// we have to decrease the max of left part <== this is not possible
    		// or decrease the min of right part

    		// a[n - 1] - a[ind] <= left_diff
    		// a[ind] >= a[n - 1] - left_diff
    		// but, ind: [1, i - 0]

    		int ind = upper_bound(a.begin() + 1, a.begin() + i, a[n - 1] - left_diff) - a.begin();
    		for(int rep = 0; rep < 3; rep++) {
	    		if(in_range(ind - rep, 1, i - 2))
	    			ans = min(ans, abs((a[n - 1] - a[ind - rep]) - left_diff));
    		}
    	}
    }
    cout << ans << endl;
}

void brute_force(int n, vector<int> &a) {
	debug(a);
	int m = (1 << n) - 1, ans = inf, minL, maxL, minR, maxR;
	for(int i = 1; i < m; i++) {
		int x = i, one_part = 0;

		minL = minR = inf;
		maxL = maxR = -inf;
		for(int j = 0; j < n; j++) {
			if(x & 1) {
				// include in subset
				minL = min(minL, a[j]);
				maxL = max(maxL, a[j]);
			} else {
				// don't include in subset
				minR = min(minR, a[j]);
				maxR = max(maxR, a[j]);
			}
			x >>= 1;
		}
		ans = min(ans, abs((maxR - minR) - (maxL - minL)));

		debug(i);
		debug(minL, maxL);
		debug(minR, maxR);
	}
	cout << ans << endl << endl;
}

void solve(int tc) {
    int n;
    cin >> n;

    vector<int> a(n);
    cin >> a;

    // optimal(n, a);
    brute_force(n, a);
}

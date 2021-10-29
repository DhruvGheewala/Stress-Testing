/**
  *  Author: dhruv_gheewala
  *  Problem: Equal Beauty
  *  Date:   25.10.2021
  *  Time:   22:29:02
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

void solve(int tc) {
    int n;
    cin >> n;

    vector<int> a(n);
    cin >> a;
    sort(a.begin(), a.end());

    const auto &cost = [&](int elem1, int elem2) {
    	int result = abs((elem1 - a[0]) - (a.back() - elem2));
    	result = min(result, abs((elem2 - a[0]) - (a.back() - elem1)));
    	return result;
    };

    // Now we have to select 2 elems such that
    // abs((elem1 - a[0]) - abs(a[n - 1] - elem2)) is minimized

    // here elem1 = a[i]
    // we will search for elem2
    //
    // here, elem1 can't be a[n - 1]
    // and elem2 can't be a[0]

    int ans = inf; // 0
    for(int i = 0; i < n - 1; i++) {
    	// elem2 = a[i + 1]
    	ans = min(ans, cost(a[i], a[i + 1]));

    	// Find elem2 in: [1, i - 1]
    	int l = 1, r = i - 1, mid;
		int left_part = a[i] - a[0];

    	while(l <= r) {
    		mid = (l + r) / 2;
    		int right_part = a[n - 1] - a[mid];
    		ans = min(ans, abs(right_part - left_part));

    		if(left_part < right_part) {
    			l = mid + 1; // right_part will decrease
    		} else {
    			r = mid - 1; // right_part will increase
    		}
    	}
    }
    cout << ans << endl;
}

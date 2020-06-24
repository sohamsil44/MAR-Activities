/*
#MAR
#MAKAUT
#Coding_solution
Permutation Distance  Problem Code: PERMDIST
Consider a permutation P=(p1,p2,...,pn) of numbers {1,2,...,n}. Let us construct a graph G(P) with n vertices as follows: if i,j∈{1,...,n} and i<j, 
then an undirected edge (i,j) is present in G(P) if and only if pi<pj.
Given a permutation P, answer several queries of the form "what is the shortest length of a path between u and v in G(P)?". 
If there is no path between u and v, report so.

Input:
The first line contains a single integer T
denoting the number of test cases. T
test case descriptions follow.
Each test case description starts with a line containing two integers, n
and q, denoting the length of the permutation P
and the number of queries respectively.
The next line contains n
distinct integers p1,...,pn denoting the permutation P
.
The following q
lines describe queries. The i-th of these lines contains two integers ui and vi denoting parameters of the i

    -th query.

Output:

    Print answers for all queries in order of appearance in the input, one per line.
    If there is no path between ui

and vi, print −1 as the answer for the i-th query. Otherwise, print a single integer denoting the shortest length of a path between ui and vi

    .

Constraints

    1≤T≤105

1≤n,q≤105
1≤pi≤n
p1,...,pn
forms a permutation of {1,2,...,n}
1≤ui,vi≤n
The sum of all n
in a test file does not exceed 5⋅105
The sum of all q
in a test file does not exceed 5⋅105

Sample Input:

1
5 4
3 5 2 4 1
1 1
2 3
1 4
4 5

Sample Output:

0
3
1
-1

Explanation

    In the first query, we can go from 1 to 1 by just staying there, and hence path of length 0.
    In the second query, we can go from the 2 (which has the value p2=5

) to 1, because 1 < 2 and p1<p2. From there, we can go to 4, and from there to 3. This gives us a path of length 3, and is the shortest that we can get.

*/

#include<bits/stdc++.h>
using namespace std;
typedef long double db;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<db, db> pdd;
#define fi first
#define se second
#define empb emplace_back
#define all(x) (x).begin(),(x).end()
const int N = 1e5 + 10;
const int LOGN = 18;
int nxt[N][LOGN];
int pre[N], gsu[N], p[N], a[N];
int main() {
#ifdef local
	freopen("in.txt", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int _; cin >> _;
	while(_--) {
		int n, q; cin >> n >> q;
		for(int i = 1; i <= n; i++) cin >> a[i], p[a[i]] = i;
		for(int i = 1; i <= n; i++) {
			pre[i] = i;
			if(i > 1 && a[pre[i - 1]] < a[i]) pre[i] = pre[i - 1];
		}
		for(int i = n; i; i--) {
			gsu[i] = p[i];
			if(i < n) gsu[i] = max(p[i], gsu[i + 1]);
		}
		for(int i = 1; i <= n; i++) nxt[i][0] = gsu[a[pre[i]]];
		int lgn = __lg(n) + 1;
		for(int j = 1; j <= lgn; j++)
			for(int i = 1; i <= n; i++)
				nxt[i][j] = nxt[nxt[i][j - 1]][j - 1];
		auto solve = [&](int l, int r) {
			if(l == r) return 0;
			if(l > r) swap(l, r);
			if(a[l] < a[r]) return 1;
			int ret = 0;
			for(int i = lgn; i >= 0; i--) {
				if(nxt[l][i] < r) {
					l = nxt[l][i];
					ret += 2 << i;
				}
			}
			if(nxt[l][0] < r) return -1;
			l = pre[l]; ret += 2;
			if(a[l] > a[r]) ret++;
			return ret;
		};
		while(q--) {
			int l, r; cin >> l >> r;
			if(l > r) swap(l, r);
			int ans = solve(l, r);
			if(ans != -1) ans = min(ans, solve(gsu[a[l]], r) + 1);
			cout << ans << '\n';
		}
	}
	return 0;
}

/*
1
4 1
1 4 2 3
2 3
*/

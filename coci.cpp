/*
    -Use mo's algorithm to get the count for every element for every query in O(N*sqrt(N)) for all queries.
    -If we split the query into segments(segment tree), the majority element in the whole range has to be the majority element in some segment of it. So we have log n candidates for the majority element for every query.
*/
#define fast ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <bits/stdc++.h>
using namespace std;
#define sqr 500
#define mid (l+r)/2
#define pb push_back
#define ppb pop_back
#define fi first
#define se second
#define lb lower_bound
#define ub upper_bound
#define ins insert
#define era erase
#define C continue
#define mem(dp,i) memset(dp,i,sizeof(dp))
#define mset multiset
typedef long long ll;
typedef short int si;
typedef long double ld;
typedef pair<int,int> pi;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pi> vpi;
typedef vector<pll> vpll;
const ll inf=1e18;
const ld pai=acos(-1);
int n , m , q ;
int a [300009] , ans [10009] ;
pair < pi , int > que [10009] ;

// mo 
bool cmp ( pair < pi , int > a , pair < pi , int > b ) {
	if ( a.fi.fi / sqr == b.fi.fi / sqr ) return a.fi.se < b.fi.se ;
	return a.fi.fi < b.fi.fi ;
} 
int s = 0 , e = -1 ;
int num [10009] ;
void mo ( int l , int r ) {
	while ( e < r ) {
		e ++ ;
		num [ a[e] ] ++ ;
	}
	while ( e > r ) {
		num [ a[e] ] -- ;
		e -- ;
	}
	while ( s < l ) {
		num [ a[s] ] -- ;
		s ++ ;
	}
	while ( s > l ) {
		s -- ;
		num [ a[s] ] ++ ;
	}
}

// segtree
int tree[2000009] ;
void build ( int node , int l , int r ) {
	int who = 0 , crnt = 0 ;
	for ( int i = l ; i <= r ; i ++ ) {
		if ( crnt == 0 ) who = a[i] , crnt ++ ;
		else if ( a[i] == who ) crnt ++ ;
		else crnt -- ;
	}
	tree [node] = who ;
	if ( l == r ) return ;
	build ( node*2 ,l, mid ) ;
	build ( node*2+1,mid+1,r ) ;
}
vi query ( int node , int l , int r , int s , int e ) {
	if ( l > r || e < l || s > r ) {
		vi ret;
		return ret;
	}
	if ( s <= l && e >= r ) {
		vi ret;
		ret.pb ( tree[node] ) ;
		return ret ;
	}
	vi left = query ( node*2,l,mid,s,e) ;
	vi right = query ( node*2+1,mid+1,r,s,e) ;
	for ( auto u :right ) left .pb ( u ) ;
	return left ;
}

int main () {
	scanf("%d%d",&n,&m);
	for ( int i = 0 ; i < n ; i ++ ) scanf("%d",&a[i]) ; 
	scanf("%d",&q);
	for ( int i = 0 ; i < q ; i ++ ) {
		int l , r ;
		scanf("%d%d",&l,&r);
		l -- , r -- ;
		que[i] = { { l , r } , i } ;
	}
	sort ( que , que + q , cmp ) ;
	build ( 1 , 0 , n -1 ) ;
	for ( int i = 0 ; i < q ; i ++ ) {
		int l = que[i].fi.fi , r = que[i].fi.se , id = que[i].se ;
		mo ( l , r ) ;
		int goal = ( r - l + 1 ) / 2 ;
		int who = -1 ;
		vi ret = query ( 1 , 0 , n - 1 , l , r ) ;
		for ( auto u : ret ) {
			if ( num [ u ] > goal ) {
				who = u ;
			}
		}
		ans [ id ] = who ;
	}
	for ( int i = 0 ; i < q ; i ++ ) {
		if ( ans [i] == -1 ) printf("no\n") ;
		else printf("yes %d\n",ans[i]) ;
	}
}

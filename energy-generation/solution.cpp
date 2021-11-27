//pragma
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

#define YOU using
#define DONT namespace
#define SAY std

YOU DONT SAY;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ll,int> pli;
typedef pair<int,ll> pil;
typedef vector<int> vi;
typedef vector<pii> vii;
typedef vector<pll> vll;

#define REPP(i,a,b,d) for(int i=a;i<=b;i+=d)
#define REP(i,a,b) REPP(i,a,b,1)
#define REVV(i,a,b,d) for(int i=a;i>=b;i-=d)
#define REV(i,a,b) REVV(i,a,b,1)

#define FOR(i,a) for(int i=0; i<a; i++)
#define FORD(i,a) for(int i=(int)a-1; i>=0; i--)

#define ALL(v) v.begin(), v.end()

#define pb push_back
#define F first
#define S second

const int OO = 1e9;
const ll INF = 1e18;

const int irand(int lo,int hi){
	return ((double)rand()/(RAND_MAX + 1.0)) * (hi-lo+1) + lo;
}

const ll lrand(ll lo,ll hi){
	return ((double)rand()/(RAND_MAX + 1.0)) * (hi-lo+1) + lo;
}

#define getc getchar
template<typename T>
T getnum(){
	int sign = 1;
	T ret = 0;
	char c;

	do{
		c = getc();
	}while(c == ' ' || c == '\n');
	if(c == '-')sign = -1;
	else ret = c-'0';
	while(1){
		c = getc();
		if(c < '0' || c > '9')break;
		ret = 10*ret + c-'0';
	}
	return sign * ret;
}

inline void ini(int& x){
	x = getnum<int>();
}

inline void scani(int& x){
	scanf("%d",&x);
}

//end of macro

const int N = 105; // nodes numbered 1..N-2
const int SRC = 0; // source
const int SINK = N-1; // sink

struct edge{int to, flow, cap, rev;};
vector<edge> lst[N]; // adjlist

void addEdge(int a, int b, int cap){
    int sa = lst[a].size(), sb = lst[b].size();
    lst[a].pb({b, 0, cap, sb});
    lst[b].pb({a, 0, cap, sa}); // here cap=cap cuz 2 way
}

int level[N]; // level graph
int lastEdge[N]; // to keep used paths from being flowed again

bool bfs(){ // create level graph, returns false if no more flow is possible
    queue<int>q;
    memset(level, -1, sizeof level);

    q.push(SRC);
    level[SRC] = 0;
    while(!q.empty()){
        int now = q.front();
        q.pop();

        FOR(i,lst[now].size()){
            edge& e = lst[now][i];
            if(level[e.to] != -1)continue;
            if(e.flow < e.cap){ // flow still possible
                level[e.to] = level[now]+1;
                q.push(e.to);
            }
        }
    }
    return level[SINK] != -1;
}

int dfs(int now, int flow){ // do the flow
    if(now == SINK)return flow;

    int ret = 0;
    for(int& i = lastEdge[now]; i<lst[now].size(); i++){
        edge& e = lst[now][i];
        if(e.flow == e.cap)continue; // no flow
        if(level[e.to] == level[now]+1){
            int curr = dfs(e.to, min(flow, e.cap - e.flow));
            if(curr > 0){
                e.flow += curr; // forward flow
                lst[e.to][e.rev].flow -= curr; // residual
                flow -= curr;
                ret += curr;
                if(flow == 0)return ret; // if flow to this node is already depleted, i.e. there is a bottleneck far before this node
            }
        }
    }
    return ret;
}

int maxFlow(){
    int ret = 0;
    while(bfs()){
        memset(lastEdge, 0, sizeof lastEdge);
        ret += dfs(SRC, OO);
    }
    return ret;
}

int n,r,g,p;
int x[N], y[N];
/*
nodes
1..n = orientation of x
n+1..2n = orientation of y

positive connects to src
negative connects to sink
*/

int dist2(int x1, int y1, int x2, int y2) {
    return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    #define endl '\n'
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(10);

    cin>>n>>r>>g>>p;
    g *= 2;
    REP(i,1,n) {
        int ori, sx, sy;
        cin>>x[i]>>y[i]>>ori;
        if(ori == 0 || ori == 90) {
            // positive x
            addEdge(SRC, i, p);
        } else {
            // negative x
            addEdge(i, SINK, p);
        }
        if(ori == 0 || ori == 270) {
            // positive y
            addEdge(SRC, n+i, p);
        } else {
            // negative y
            addEdge(n+i, SINK, p);
        }
    }
    // interactions
    int interactions = 0;
    REP(i,1,n) {
        REP(j,i+1,n) {
            if(dist2(x[i], y[i], x[j], y[j]) > r * r) {
                continue;
            }
            if(x[i] == x[j] || y[i] == y[j]) {
                continue;
            }
            addEdge(i, j, g);
            addEdge(n+i, n+j, g);
            interactions++;
        }
    }

    int ans = p * n; // tower passive
    ans += interactions * g; // optimal interaction = g
    int mf = maxFlow();
    ans -= mf;

    // cout << mf << endl;
    cout << ans << endl;

    return 0;
}

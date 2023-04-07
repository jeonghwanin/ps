#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

/*
dfs, 정렬, 비교
*/
struct Edge {
	int to;
	int cost;
};

struct cmp {
	bool operator()(Edge c, Edge p) {
		if (p.cost < c.cost) return true;
		if (p.cost > c.cost) return false;
		return false;
	}
};

vector<Edge>E[1001];
bool visited[1001];
vector<int> path;
int N, P, K;
int MIN = 21e8;
bool Find = false;
priority_queue < int, vector<int>, greater<int>>pq;
/*
void dijkstra(void) {
	int dist[1001];
	for (int t = 0; t < 1001; ++t) {
		dist[t] = 21e8;
	}
	priority_queue<Edge, vector<Edge>, cmp>pq;
	dist[1] = 0;
	pq.push({ 1, 0 });

	while (!pq.empty()) {
		Edge now = pq.top(); pq.pop();
		path.push_back(now.to);
		if (dist[now.to] < now.cost) continue;
		for (int t = 0; t < E[now.to].size(); ++t) {
			Edge next = E[now.to][t];
			int ncost;
			if (next.cost < dist[now.cost]) ncost = dist[now.cost];
			else ncost = next.cost;
			if (dist[next.to] <= ncost) continue;
			dist[next.to] = ncost;
			pq.push({ next.to, ncost });
		}
	}
	if (dist[N] == 21e8) return;
	else {
		vector<int>tmp;
		for (int t = 0; t < path.size(); ++t) {
			tmp.push_back()
		}
		sort(path.rbegin(), path.rend());
		MIN = path[K];
		return;
	}
}
*/
void dfs(int i,int level){
	if (i == N) {
		Find = true;
		vector<int> tmp = path;
		if (tmp.size() <= K) {
			MIN = 0;
			return;
		}
		sort(tmp.rbegin(), tmp.rend());
		if (MIN > tmp[K]) {
			MIN = tmp[K];
		}
		return;
	}

	for (int t = 0; t < E[i].size(); ++t) {
		if (visited[E[i][t].to]) continue;
		if (level > K && pq.top() >= MIN) continue;
		priority_queue < int, vector<int>, greater<int>>tmp = pq;
		
		visited[E[i][t].to] = true;
		path.push_back(E[i][t].cost);
		pq.push(E[i][t].cost);
		dfs(E[i][t].to,level);
		visited[E[i][t].to] = false;
		path.pop_back();
		pq = tmp;
	}
	
}

int main(void) {
	

	cin >> N >> P >> K;

	for (int t = 0; t < P; ++t) {
		int a, b, c;
		cin >> a >> b >> c;
		E[a].push_back({ b,c });
		E[b].push_back({ a,c });
		path.push_back(c);
	}
	sort(path.rbegin(), path.rend());
	MIN = path[K];
	path.clear();
	visited[1] = true;
	dfs(1, 0);
	if (!Find) {
		cout << -1;
		return 0;
	}
	
	cout << MIN;

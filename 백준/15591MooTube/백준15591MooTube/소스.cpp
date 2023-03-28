#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <queue>
#include <cstring>
#include <vector>
struct Node {
	int a;
	int cost;
};
std::vector<Node>v[5001];
bool visited[5001];
int main(void) {
	int N, Q, p, q, r, k;
	scanf("%d %d", &N, &Q);
	for (int t = 0; t < N - 1; ++t) {
		scanf("%d %d %d", &p, &q, &r);
		v[p].push_back({ q, r });
		v[q].push_back({ p, r });
	}
	for(int t=0; t<Q; ++t){
		scanf("%d %d", &k, &r);
		
		int cnt = 0;
		std::queue<Node>q;
		for (int t = 1; t <= N; ++t)
			visited[t] = false;
		q.push({ r, 2100000000 });
		visited[r] = true;
		while (!q.empty()) {
			Node now = q.front(); q.pop();
			if (now.cost >= k) ++cnt;
			for (int t = 0; t < v[now.a].size(); ++t) {
				Node next = v[now.a][t];
				int ncost = next.cost;
				if (ncost == 0) continue;
				if (visited[next.a] == true) continue;
				visited[next.a] = true;
				if (ncost > now.cost) ncost = now.cost;
				q.push({ next.a, ncost});
			}
		}
		--cnt;
		printf("%d\n", cnt);

	}


}
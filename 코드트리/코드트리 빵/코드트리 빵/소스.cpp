#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
/*
bfs
*/
struct Cor {
	int y;
	int x;
};
struct Node {
	int y;
	int x;
	vector<int>dir;
};
int n, m;
int direct[4][2] = { -1,0,0,-1,0,1,1,0 };
int map[15][15];
Cor dest[31];
Cor people[31];
vector<int>path[31];
int dat[31]; // 0이면 없음 1이면 있음 2이면 완료
vector<int> bfs1(int sy, int sx, int ey, int ex) {
	queue<Node>q;
	q.push({ sy,sx, vector<int>()});
	int visited[15][15] = { 0, };
	visited[sy][sx] = 1;
	while (!q.empty()) {
		Node now = q.front(); q.pop();
		if (now.y == ey && now.x == ex) return now.dir;
		for (int t = 0; t < 4; ++t) {
			int dy = now.y + direct[t][0];
			int dx = now.x + direct[t][1];
			if (dy < 0 || dy >= n || dx < 0 || dx >= n) continue;
			if (visited[dy][dx] > 0) continue;
			if (map[dy][dx] == 2) continue;
			visited[dy][dx] = visited[now.y][now.x] + 1;
			vector<int>path = now.dir;
			path.push_back(t);
			q.push({ dy,dx, path});
		}
	}
}
Cor bfs2(int sy, int sx) {
	int min_dist = -1;
	Cor ret;
	queue<Cor>q;
	q.push({sy,sx});
	int visited[15][15] = { 0, };
	visited[sy][sx] = 1;
	while (!q.empty()) {
		Cor now = q.front(); q.pop();
		if (min_dist != -1 && visited[now.y][now.x] > min_dist) break;
		if (visited[now.y][now.x] == min_dist && map[now.y][now.x] == 1) {
			if (now.y < ret.y) ret = { now.y, now.x };
			else if (now.y == ret.y && now.x < ret.x) ret = { now.y, now.x };
		}
		if (min_dist == -1 && map[now.y][now.x] == 1) {
			min_dist = visited[now.y][now.x];
			ret = { now.y, now.x };
		}
		for (int t = 0; t < 4; ++t) {
			int dy = now.y + direct[t][0];
			int dx = now.x + direct[t][1];
			if (dy < 0 || dy >= n || dx < 0 || dx >= n) continue;
			if (visited[dy][dx] > 0) continue;
			if (map[dy][dx] == 2) continue;
			visited[dy][dx] = visited[now.y][now.x] + 1;
			q.push({ dy,dx});
		}
	}
	return ret;
}
int sv(void) {
	int cnt = m;
	int ret = 0;
	bool reset = true;
	while (1) {
		++ret;
		//이동하기
		if (reset) {
			for (int t = 1; t <= m; ++t) {
				if (dat[t] == 1) {
					path[t] = bfs1(people[t].y, people[t].x, dest[t].y, dest[t].x);
				}
			}
		} 
		reset = false;
		for (int t = 1; t <= m; ++t) {
			if (dat[t] == 1) {

				people[t].y = people[t].y + direct[path[t][0]][0];
				people[t].x = people[t].x + direct[path[t][0]][1];
				path[t].erase(path[t].begin());

				if (people[t].y == dest[t].y && people[t].x == dest[t].x) {
					map[people[t].y][people[t].x] = 2;
					dat[t] = 2;
					cnt--;
					if (cnt == 0) return ret;
					reset = true;
				}
			} 
		}
		//base camp 들어가기
		if (ret <= m) {
			reset = true;
			Cor now = bfs2(dest[ret].y, dest[ret].x);
			people[ret] = now;
			map[now.y][now.x] = 2;
			dat[ret] = 1;
		}
	}
}
int main(void) {
	scanf("%d %d", &n, &m);
	for (int y = 0; y < n; ++y) {
		for (int x = 0; x < n; ++x) scanf("%d", &map[y][x]);
	}
	for (int t = 1; t <= m; ++t) {
		int a, b;
		scanf("%d %d", &a, &b);
		--a, --b;
		dest[t] = { a,b };
	}
	printf("%d", sv());


}


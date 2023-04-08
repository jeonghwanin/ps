#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <cstring>
struct Node {
	int y, x;
};
char map[300][301];
int N;
bool visited[300][300];
int cnt;
int direct[8][2] = { -1,-1,-1,0,-1,1,0,-1,0,1,1,-1,1,0,1,1 };
Node q[90000];
int q_size;
int sum;
void bfs(int y, int x)
{
	for (int t = 0; t < 8; t++)
	{
		int dy = y + direct[t][0];
		int dx = x + direct[t][1];
		if (dy < 0 || dx < 0 || dy >= N || dx >= N) continue;
		if (visited[dy][dx] == true) continue;
		q[q_size++] = { dy,dx };
		visited[dy][dx] = true;
		cnt--;
	}
	while (q_size != 0) {
		Node now = q[q_size - 1]; q_size--; 
		bool flag = true;
		for (int t = 0; t < 8; t++) {
			
			int dy = now.y + direct[t][0];
			int dx = now.x + direct[t][1];
			if (dy < 0 || dx < 0 || dy >= N || dx >= N) continue;
			if (map[dy][dx] == '*') {
				flag = false;
				break;
			}
		}
		if (!flag) continue;
		
		for (int t = 0; t < 8; t++) {
			int dy = now.y + direct[t][0];
			int dx = now.x + direct[t][1];
			if (dy < 0 || dx < 0 || dy >= N || dx >= N) continue;
			if (visited[dy][dx] == true) continue;
			visited[dy][dx] = true;
			cnt--;
			q[q_size++] = { dy,dx };
		}
	}
}

int main(void)
{
	int T;
	scanf("%d", &T);

	for (int tc = 1; tc <= T; tc++)
	{
		scanf("%d", &N);
		cnt = 0;
		sum = 0;
		memset(visited, 0, sizeof(visited));
		for (int y = 0; y < N; y++)
		{
			scanf("%s", map[y]);
			for (int x = 0; x < N; x++)
			{
				if (map[y][x] == '.') cnt++;
			}
		}
		for (int y = 0; y < N; y++)
		{
			for (int x = 0; x < N; x++)
			{
				if (map[y][x] == '.' && visited[y][x] == false)
				{
					bool flag = true;
					for (int t = 0; t < 8; t++) {
						int dy = y + direct[t][0];
						int dx = x + direct[t][1];
						if (dy < 0 || dx < 0 || dy >= N || dx >= N) continue;
						if (map[dy][dx] == '*') {
							flag = false;
							break;
						}
					}
					if (!flag) continue;
					visited[y][x] = true;
					bfs(y, x);
					cnt--;
					sum++;
				}
			}
		}
		printf("#%d %d\n", tc, cnt + sum);
	}
}
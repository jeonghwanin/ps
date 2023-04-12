#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int N, M;
int map[100][100];
int direct[4][2] = { -1,0,0,-1,0,1,1,0 };
void trail(int y, int x) {
	int dir = 0;
	map[y][x] = 1;
	while (dir < 4) {
		int dy = y + direct[dir][0];
		int dx = x + direct[dir][1];
		if (map[dy][dx] == 1 || (dy < 0 || dy >= N || dx < 0 || dx >= N) ) {
			dir++;
			continue;
		}
		map[dy][dx] = 1;
		y = dy;
		x = dx;
		dir = 0;
	}
	return;
}
int sv(void) {
	int ret = 0;
	for (int y = 0; y < N; ++y) {
		for (int x = 0; x < N; ++x) {
			if (map[y][x] == 0) {
				trail(y, x);
				++ret;
			}
		}
	}
	return ret;
}
int main(void) {
	scanf("%d %d", &N, &M);
	for (int t = 0; t < M; ++t) {
		int y, x;
		scanf("%d %d", &y, &x);
		map[y][x] = 1;
	}
	printf("%d", M);


}
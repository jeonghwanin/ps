#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int block[4][3][2] = {
	{{0,0},{0,1},{1,0}},
	{{0,0},{0,1},{1,1}},
	{{0,0},{1,0},{1,1}},
	{{0,0},{1,0},{1,-1}}
};
char map[20][21];
int cnt;
int ans;
int H, W;
bool isValid(int y, int x, int type) {
	for (int t = 0; t < 3; ++t) {
		int dy = y + block[type][t][0];
		int dx = x + block[type][t][1];
		if (dy < 0 || dy >= H || dx < 0 || dx >= W) return false;
		if (map[dy][dx] == '#') return false;
	}
	return true;
}
void cover(int y, int x, int type, char c) {
	for (int t = 0; t < 3; ++t) {
		int dy = y + block[type][t][0];
		int dx = x + block[type][t][1];
		map[dy][dx] = c;
	}
	return;
}
void sv(int level) {
	if (level == cnt / 3) {
		++ans;
		return;
	}
	for (int y = 0; y < H; ++y) {
		for (int x = 0; x < W; ++x) {
			if (map[y][x] == '#') continue;
			for (int t = 0; t < 4; ++t) {
				if (!isValid(y, x, t)) continue;
				cover(y, x, t, '#');
				sv(level + 1);
				cover(y, x, t, '.');
			}
			return;
		}
	}
}

int main(void) {
	int C;
	scanf("%d", &C);
	
	for (int c = 0; c < C; ++c) {
		scanf("%d %d", &H, &W);
		cnt = 0;
		ans = 0;
		for (int y = 0; y < H; ++y) {
			scanf("%s", map[y]);
			for (int x = 0; x < W; ++x) {
				if (map[y][x] == '.') ++cnt;
			}
		}
		if (cnt % 3 != 0) printf("0\n");
		else {
			sv(0);
			printf("%d\n", ans);
		}
	}

}
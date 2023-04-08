#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int map[2000][2000];
int pa[2000][2000];

int hash(int v, int p) {
	return v * p;
}

int main(void) {
	int e1 = 2;
	int e2 = 3;
	int H, W, M, N,T;
	char c;
	int pa_h1, pa_h2, ma_h1, ma_h2, po1, po2;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; ++tc) {
		scanf("%d %d %d %d", &H, &W, &N, &M);
		for (int y = 0; y < H; y++) {
			for (int x = 0; x < W; x++) {
				scanf("%c", &c);
				if (c == 'o') pa[y][x] = 0;
				else pa[y][x] = 1;
			}
		}
		for (int y = 0; y < N; y++) {
			for (int x = 0; x < M; x++) {
				scanf("%c", &c);
				if (c == 'o') map[y][x] = 0;
				else map[y][x] = 1;
			}
		}
		pa_h1 = 0, ma_h2 = 0, ma_h1 = 0, ma_h2 = 0;
		po1 = 1, po2 = 1;
		for(int y=0; y<)
	}
}
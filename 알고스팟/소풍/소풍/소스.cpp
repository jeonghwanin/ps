#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
int map[10][10];
int dat[10];

int cnt;
int C, n, m, a, b;

void sv(int level, int i) {
	if (level == n) {
		++cnt;
		return;
	}
	
	for (int t = i+1; t < n; ++t) {
		if (dat[t] == 1) continue;
		if (level & 1) {
			//È¦¼ö¸é
			if (map[i][t] != 1)continue;
			dat[t] = 1;
			sv(level + 1, i);
			dat[t] = 0;
		}
		else {
			//Â¦¼ö¸é
			dat[t] = 1;
			sv(level + 1, t);
			dat[t] = 0;
		}
	}
}

int main(void) {
	
	scanf("%d", &C);
	for (int c = 0; c < C; ++c) {
		scanf("%d %d", &n, &m);
		memset(map, 0, sizeof(map));
		memset(dat, 0, sizeof(dat));
		for (int t = 0; t < m; ++t)
		{
			scanf("%d %d", &a, &b);
			map[a][b] = 1;
			map[b][a] = 1;
		}
		cnt = 0;
		sv(0,-1);
		printf("%d\n", cnt);
	}
}
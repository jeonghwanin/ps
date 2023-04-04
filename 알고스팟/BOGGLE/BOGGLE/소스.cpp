#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
struct Node {
	int y;
	int x;
};


char map[5][6];
char find[11];
bool flag;
int direct[8][2] = { -1,-1,-1,0,-1,1,0,-1,0,1,1,-1,1,0,1,1 };
bool dp[5][5][11];

void sv(Node now, int level) {
	if (flag == true) return;
	if (dp[now.y][now.x][level]) return;
	if (map[now.y][now.x] != find[level]) return;
	if (level == strlen(find)-1) {
		flag = true;
		return;
	}
	
	bool f = false;
	
	for (int t = 0; t < 8; ++t) {
		int dy = now.y + direct[t][0];
		int dx = now.x + direct[t][1];
		if (dy < 0 || dx < 0 || dy >= 5 || dx >= 5)continue;
		sv({ dy,dx }, level + 1);
		f = true;
	}
	if (!f) dp[now.y][now.x][level - 1] = true;
}

int main(void) {
	int C, N;
	scanf("%d", &C);
	for (int t = 0; t < C; ++t) {
		for (int q = 0; q < 5; ++q) {
			scanf(" %s", map[q]);
		}

		scanf("%d", &N);
		for (int r = 0; r < N; ++r) {
			scanf(" %s", find);
			flag = false;
			memset(dp, 0, sizeof(dp));
			for (int y = 0; y < 5; ++y) {
				for (int x = 0; x < 5; ++x) {
					if (flag) break;
					sv({ y,x }, 0);
				}
				if (flag) break;
			}
			
			if (flag == false) printf("%s, NO\n", find);
			else printf("%s, YES\n",find);
			
		}
		
	}
}
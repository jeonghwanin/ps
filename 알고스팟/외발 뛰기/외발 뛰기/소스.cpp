#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <cstring>
int n;
int map[100][100];
int check[100][100];
int sv(int y, int x) {

	if (y < 0 || y >= n || x < 0 || x >= n) return 0;
	if (y == n - 1 && x == n - 1) return 1;
	if(check[y][x] == -1) return check[y][x] = sv(y + map[y][x], x) || sv(y, x + map[y][x]);
	return check[y][x];
	
}
    
int main(void) {
	int C;
	scanf("%d", &C);

	for (int c = 0; c < C; ++c) {
		scanf("%d", &n);
		for (int y = 0; y < n; ++y)
			for (int x = 0; x < n; ++x)
				scanf("%d", &map[y][x]);
		memset(check, -1, sizeof(check));
		if (sv(0,0)) printf("YES\n");
		else printf("NO\n");
	}
}
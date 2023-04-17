#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int N, M;
int map[102][102];
int direct[4][2] = { -1,0,0,-1,0,1,1,0 };
struct Node {
	int y, x;
	int nth;
	bool start;
	bool end;
};
int dat[102][102];
int ans;
int nth;

void sv2(int y, int x) {
	map[y][x] = 1;
	Node finish = { y,x,++nth,false, false };
	if (dat[y - 1][x] != 0) {
		finish.start = true;
		finish.nth = dat[y - 1][x];
	}
	else {
		if (map[y + 1][x] == 1) {
			finish.start = true;
		}
	}
	while (1) {
		if (x - 1 < 0) break;
		if (map[y-1][x - 1] != 0) {
			map[y][x - 1] = 0;
			--x;
		}
		else {

		}

		

		if (finish.start && finish.end) ++ans;
	}
}

void sv(void) {
	for (int y = 1; y <= N; ++y) {
		if (y % 2 == 0) {
			//왼쪽으로
			for (int x = N; x >= 1; --x) {
				if (map[y][x] == 0) {
					sv2(y, x);
				}
			}
		}
		else {
			//오른쪽으로
			for (int x = 1; x <= N; ++x) {
				if (map[y][x] == 0) {
					sv3(y, x);
				}
			}
		}
	}
}

int main(void) {
	scanf("%d %d", &N, &M);
	for (int t = 0; t <= N + 1; ++t) {
		map[t][0] = 1;
		map[t][N + 1] = 1;
		map[0][t] = 1;
		map[N + 1][t] = 1;
	}
	for (int t = 0; t < M; ++t) {
		int y, x;
		scanf("%d %d", &y, &x);
		map[y][x] = 1;
	}
	printf("%d", M);


}
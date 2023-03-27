#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <queue>

int arr[5001][5001];
int MIN(int a, int b, int c) {
	if (a <= b && a <= c) return a;
	if (b <= a && b <= c) return b;
	if (c <= a && c <= b) return c;
}
int main(void) {
	int N, Q, p, q, r, k, ans;
	scanf("%d %d", &N, &Q);

	for (int y = 1; y <= N; ++y)
		for (int x = 1; x<= N; ++x) {
			arr[y][x] = 1e9;
			arr[y][y] = 0;
		}
	for (int t = 0; t < N-1; ++t){
		scanf("%d %d %d", &p, &q, &r);
		arr[p][q] = r;
		arr[q][p] = r;
	}

	for (int t = 1; t <= N; ++t) {
		for (int q = 1; q <= N; ++q) {
			for (int w = 1; w <= N; ++w) {
				if (q == w || q==t||w==t) continue;
				arr[q][w] = MIN(arr[q][w], arr[q][t], arr[w][t]);
			}
		}
	}
	for (int t = 1; t <= N; ++t) {
		for (int q = 1; q <= N; ++q)
			printf("%d", arr[t][q]);
		printf("\n");
	}
	for (int t = 0; t < Q; ++t) {

		ans = 0;
		scanf("%d %d", &p, &k);
		for (int q = 1; q <= N; ++q) {
			if (arr[p][q] != 0 && arr[p][q] >= k)++ans;
		}
		printf("%d\n", ans);
	}
	
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int copy[500000];
int n[500000];
int m[500000];
int MIN, cnt, N, M;
int SUB(int a, int b) {
	if (a >= b)return a - b;
	else return b - a;
}
void merge(int start, int end, int arr[]) {
	int mid = (start + end) >> 1;
	int i = start;
	int j = mid + +1;
	int k = 0;
	while (i <= mid && j <= end) {
		if (arr[i] <= arr[j]) copy[k++] = arr[i++];
		else copy[k++] = arr[j++];
	}
	while(i<=mid) copy[k++] = arr[i++];
	while(j<=end) copy[k++] = arr[j++];
	for (i = start; i <= end; ++i)
		arr[i] = copy[i - start];
}

void sort(int start, int end, int arr[]) {
	if (start < end) {
		int mid = (start + end) >> 1;
		sort(start, mid, arr);
		sort(mid + 1, end, arr);
		merge(start, end, arr);
	}
}

void bs(void) {
	MIN = 21e8;

	for (int y = 0; y < N; ++y) {
		int start = 0;
		int end = M - 1;
		int ans = M - 1;
		while (start <= end) {
			int mid = (start + end) >> 1;			
			if (n[y] <= m[mid]) {
				ans = mid;
				end = mid - 1;
			}
			else {
				start = mid + 1;
			}
		}
		int a = SUB(m[ans], n[y]);
		int b;
		b = SUB(m[ans - 1], n[y]);
		if (ans - 1 < 0)b = 21e8;
		if (a<b) {
			if (MIN > a) {
				MIN = a;
				cnt = 1;
			}
			else if (MIN == a) ++cnt;
		}
		else if (a == b) {
			if (MIN > a) {
				MIN = a;
				cnt = 2;
			}
			else if (MIN == a) cnt+=2;
		}
		else {
			if (MIN > b) {
				MIN = b;
				cnt = 1;
			}
			else if (MIN == b) ++cnt;
		}
	}
}

int main(void) {
	
	int T, c1, c2;
	scanf("%d", &T);

	for (int tc = 1; tc <= T; ++tc) {
		MIN = 21e8; cnt = 0;
		scanf("%d %d", &N, &M);
		scanf("%d %d", &c1, &c2);
		c1 = c1 - c2 >= 0 ? c1 - c2 : c2 - c1;
		for (int t = 0; t < N; ++t) {
			scanf("%d", &n[t]);
		}
		for (int t = 0; t < M; ++t) {
			scanf("%d", &m[t]);
		}
		sort(0, M - 1, m);
		bs();
		printf("#%d %d %d\n", tc, c1 + MIN, cnt);
	}
	
}
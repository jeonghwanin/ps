#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
int N;
unsigned long long M;
unsigned long long n[101];

unsigned long long bs(long long start, long long end) {
	long long ans = 0;
	while (start <= end) {
		unsigned long long mid = (start + end) >> 1;
		unsigned long long cnt = 0;
		for (int t = 1; t <= N; ++t) cnt += (n[t] / mid);
			//if (mid == 0) return ans;
			
		if (cnt >= M){
			ans = mid;
			start = mid + 1;
		}
		else {
			end = mid - 1;
		}
		
	}
	return ans;
}

int main(void) {
	int T;
	unsigned long long MAX;
	scanf("%d", &T);

	for (int tc = 1; tc <= T; ++tc) {
		scanf("%d %llu", &N, &M);
		for (int t = 1; t <= N; ++t) { 
			scanf("%llu", &n[t]); 
			if (t == 1) MAX = n[t];
			else {
				if (MAX < n[t]) MAX = n[t];
			}
		}
		printf("#%d %llu\n", tc, bs(1, MAX));
	}
}
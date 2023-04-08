#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
/*
a -> 2*a%(a+b)
*/
int a, b, k;
int sv(int a, int k) {
	long long ret = a;
	long long t = 2;
	while (k) {
		if (k & 1) { 
			ret = ret * t;
			if (ret >= b) ret %= b;
		}
		t = t * t;
		if(t>=b) t %= b;
		k >>= 1;
	}
	return ret;
}

int main(void) {
	int T, ans;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; ++tc) {
		scanf("%d %d %d", &a, &b, &k);
		b = a + b;
		int ans = sv(a, k);
		if (ans > b - ans) ans = b - ans;
		printf("#%d %d\n", tc, ans);
	}
}
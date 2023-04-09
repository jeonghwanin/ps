#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int N;
char W[101];
char S[50][101];
int main(void) {
	int C;
	scanf("%d", &C);

	for (int c = 0; c < C; ++c) {
		scanf("%d", &N);
		scanf("%s", W);
		for (int n = 0; n < N; ++n) {
			scanf("%s", S[n]);
		}

	}
}
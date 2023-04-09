#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int ladder[20000];
//[start, end]
int sv(int start, int end) {
	int MAX;
	if (start == end) {
		return ladder[start];
	}
	else {
		int mid = (start + end) / 2;
		int left_MAX = sv(start, mid);
		int right_MAX = sv(mid + 1, end);
		if (left_MAX <= right_MAX) MAX = right_MAX;
		else MAX = left_MAX;

		int height;
		if (ladder[mid] <= ladder[mid+1]) height = ladder[mid];
		else height = ladder[mid+1];
		if(MAX < 2 * height) MAX = 2 * height;

		int i = mid;
		int j = mid + 1;
		while (i > start || j < end) {
			if (j < end && (i == start || ladder[i - 1] < ladder[j + 1])) {
				++j;
				if (ladder[j] <= height) height = ladder[j];
			}
			else {
				--i;
				if (ladder[i] <= height) height = ladder[i];
			}
			if (MAX < (j - i + 1) * height) MAX = (j - i + 1) * height;
		}
		
	}
	return MAX;
}

int main(void) {
	int C, N;
	scanf("%d", &C);
	for (int c = 1; c <= C; ++c) {
		scanf("%d", &N);
		for (int n = 0; n < N; ++n) {
			scanf("%d", &ladder[n]);
		}
		printf("%d\n", sv(0, N - 1));
	}
}
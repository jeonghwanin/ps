#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

char arr[20000][51];
char cp[20000][51];
int getlen(const char* s) {
	int len;
	for (len = 0; s[len]; ++len);
	return len;
}

void strcp(char* a, const char* b) {
	while (*a++ = *b++);
	return;
}
int strcmp(const char* a, const char* b) {
	while (*a && *a == *b) ++a, ++b;
	return *a - *b;
}
bool cmp(const char* a, const char* b) {
	int l1 = getlen(a);
	int l2 = getlen(b);
	if (l1 < l2) return true;
	if (l1 > l2) return false;
	for (int t = 0; t < l1; ++t) {
		if (*a < *b) return true;
		if (*a > *b) return false;
		++a, ++b;
	}
	return false;
}

void merge(int start, int end) {

	int mid = (start + end) / 2;
	int i = start;
	int j = mid + 1;
	int k = 0;
	while (i <= mid && j <= end) {
		if (cmp(arr[i], arr[j])) strcp(cp[k++], arr[i++]);
		else strcp(cp[k++], arr[j++]);
	}
	while(i<=mid) strcp(cp[k++], arr[i++]);
	while(j<=end) strcp(cp[k++], arr[j++]);

	for (i = start; i <= end; ++i) {
		strcp(arr[i], cp[i - start]);
	}
}
void sort(int start, int end) {
	if (start < end) {
		int mid = (start + end) / 2;
		sort(start, mid);
		sort(mid + 1, end);
		merge(start, end);
	}
	return;
}
int main(void) {
	int T, N;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; ++tc) {
		scanf("%d", &N);
		for (int t = 0; t < N; ++t) {
			scanf(" %s", arr[t]);
		}
		sort(0, N-1);
		printf("#%d\n", tc);
		for(int t=0; t<N; ++t){
			if (t == 0) printf("%s\n", arr[t]); 
			else {
				if (!strcmp(arr[t - 1], arr[t])) {
					continue; 
				}
				printf("%s\n", arr[t]);
			}
			
		}
	}
}
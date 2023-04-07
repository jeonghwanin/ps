#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <cstring>
char str[1001];

char cp[1001];
void sv(int *index) {
	if (str[*index] == 'x'){
		++(*index);
		int a = *index;
		sv(index);
		int b = *index;
		sv(index);
		int c = *index;
		sv(index);
		int d = *index;
		sv(index);
		for (int t = c; t < *index; ++t) {
			cp[a + t - c] = str[t];
		}
		for (int t = a; t < c; ++t) {
			cp[*index-c+t] = str[t];
		}
		for (int t = a; t < *index; ++t) {
			str[t] = cp[t];
		}
	}
	else if(str[*index] != '\0') {
		++(*index);
		return;
	}
}
int main(void) {
	int C;
	scanf("%d", &C);
	for (int c = 0; c < C; ++c) {
		scanf("%s", str);
		int index = 0; 
		sv(&index);
		printf("%s\n", str);
	}
}
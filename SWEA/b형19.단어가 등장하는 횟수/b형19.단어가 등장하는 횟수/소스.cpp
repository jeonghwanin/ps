/*
문자열 s1, s2
s2의 해시값을 구함
s1의 해시값을 업데이트 하며 비교
 같으면 진짜인지 구함
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

char s1[500002], s2[100002];

int hash(int value, int power) {
	return value * power;
}



int main(void) {
	int T;
	int e1, e2, po1, po2;
	e1 = 31, e2 = 37;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		scanf(" %s", s1);
		scanf(" %s", s2);
		int len1, len2;
		for (len1 = 0; s1[len1]; ++len1);
		for (len2 = 0; s2[len2]; ++len2);
		int ph1, ph2;
		int sh1, sh2;
		int ans = 0;
		po1 = 1, po2 = 1, sh1=0, sh2=0, ph1 = 0,ph2 = 0;
		for (int t = 0; t <= len1 - len2; ++t) {
			if (t == 0) {
				for (int q = len2-1; q >= 0; --q) {
					ph1 = ph1 + po1 * s2[q];
					ph2 = ph2 + po2 * s2[q];
					sh1 = sh1 + po1 * s1[q];
					sh2 = sh2 + po2 * s1[q];

					if (t == len1 - len2) continue;
					po1 *= e1;
					po2 *= e2;
				}
			}
			else {
				sh1 = e1 * (sh1 - po1 * s1[t]) + s1[t + len2];
				sh2 = e2 * (sh2 - po2 * s1[t]) + s1[t + len2];
			}

			// 맞는 지 검사
			if (sh1 == ph1 && sh2 == ph2) ++ans;
			
		}

		printf("#%d %d\n", tc, ans);
	}
}
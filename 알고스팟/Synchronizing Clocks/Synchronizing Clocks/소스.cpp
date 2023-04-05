#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int MIN;
int clock[16];
char link[10][17] = {
	"xxx0000000000000",
	"000x000x0x0x0000",
	"0000x00000x000xx",
	"x000xxxx00000000",
	"000000xxx0x0x000",
	"x0x00000000000xx",
	"000x0000000000xx",
	"0000xx0x000000xx",
	"0xxxxx0000000000",
	"000xxx000x000x00"
};

bool isValid(void) {
	for (int t = 0; t < 16; ++t) { if (clock[t] != 12) return false; }
	return  true;
}

void sv(int level, int cnt) {
	
	if (MIN <= cnt) return;
	if (isValid()) {
		MIN = cnt;
		return;
	}
	if (level == 10) return;

	for (int q = 0; q < 4; ++q) {
		
		for (int t = 0; t < 16; ++t) {
			if (link[level][t] == 'x') {
				clock[t] += 3 * q;
				if (clock[t] > 12) clock[t] -= 12;
			}
		}
		sv(level + 1, cnt + q);

		for (int t = 0; t < 16; ++t) {
			if (link[level][t] == 'x') {
				clock[t] -= 3 * q;
				if (clock[t] <= 0) clock[t] += 12;
			}
		}
	}

}

int main(void) {
	int C;
	scanf("%d", &C);
	for (int c = 0; c < C; ++c) {
		for (int t = 0; t < 16; ++t) {
			scanf("%d", &clock[t]);
		}
		MIN = 21e8;
		sv(0,0);
		if (MIN == 21e8) MIN = -1;
		printf("%d\n", MIN);
	}
}
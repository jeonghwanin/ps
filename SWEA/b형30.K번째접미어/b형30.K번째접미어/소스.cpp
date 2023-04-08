#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <cstring>
#define SIZE 26
#define MAX_SIZE 802010
struct Trie {
	bool t;
	int child[SIZE];
	Trie() {
		t = false;
		memset(child, -1, sizeof(child));
	}
};


Trie trie[MAX_SIZE];

int main(void) {
	int T, K;
	scanf("%d", &T);

	for (int tc = 1; tc <= T; tc++)
	{
		scanf("%d", &K);
	}
}
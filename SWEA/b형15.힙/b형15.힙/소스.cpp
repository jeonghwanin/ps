#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int heap[100001];
int heap_size;

int ret[100001];
int ret_size;

void push(int data)
{
	heap[++heap_size] = data;
	for (int i = heap_size; i > 1; i /= 2)
	{
		if (heap[i / 2] >= heap[i])break;
		int tmp = heap[i / 2];
		heap[i / 2] = heap[i];
		heap[i] = tmp;
	}
}

int pop(void) {
	if (heap_size == 0) return -1;
	
	int ans = heap[1];

	heap[1] = heap[heap_size];
	heap[heap_size--] = -1;
	for (int i = 1; i * 2 <= heap_size;) {
		if (heap[i] >= heap[i * 2] && heap[i] >= heap[i * 2 + 1]) break;
		else if (heap[2 * i] >= heap[2 * i+1]) {
			int tmp = heap[i];
			heap[i] = heap[2 * i];
			heap[2 * i] = tmp;
			i = i * 2;
		}
		else {
			int tmp = heap[i];
			heap[i * 2 + 1] = heap[i];
			heap[i] = tmp;
			i = i * 2 + 1;
		}
	}
	return ans;
}
int main(void)
{
	//freopen("input.txt", "r", stdin);
	int T, N, i;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		scanf("%d", &N);
		heap_size = 0;
		ret_size = 0;
		
		for (int n = 0; n < N; n++) {
			scanf("%d", &i);
			if (i == 1) {
				scanf("%d", &i);
				push(i);
			}
			else if (i == 2) {
				ret[ret_size++] = pop();
			}
		}
		printf("#%d", tc);
		for (int t = 0; t < ret_size; t++) {
			printf(" %d", ret[t]);
		}
		printf("\n");
	}
}
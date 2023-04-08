#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int w[3];

void merge(int start, int end, int a[]) {
	int mid, i, j, k;
	mid = (start + end) >> 1;
	i = start;
	j = mid + 1;
	k = 0; //임시 배열

	while (i <= mid && j <= end) {
		if (a[i] <= a[j]) w[k++] = a[i++];
		else w[k++] = a[j++];
	}
	while (i <= mid) w[k++] = a[i++];
	while (j <= end) w[k++] = a[j++];
	for (i = start; i <= end; i++)
		a[i] = w[i - start];
}

void sort(int start, int end, int a[]) {
	
	if (start >= end) return;
	int mid = (start + end) >> 1;

	sort(start, mid, a);
	sort(mid + 1, end, a);
	merge(start, end, a);
}

// 0 : min 1: max
int heap[2][200005];
int h_size[2];
void h_init(void) {
	h_size[0] = 0;
	h_size[1] = 0;
}
bool lt(int a, int b) {
	if (a <= b) return true;
	else return false;
}
void push(int data, int M) {
	heap[M][++h_size[M]] = data;

	for ( int cur = h_size[M]; cur / 2 >= 1; cur /= 2) {
		if (M == 0) {
			if (lt(heap[M][cur / 2], heap[M][cur])) break;
			int tmp = heap[M][cur / 2];
			heap[M][cur / 2] = heap[M][cur];
			heap[M][cur] = tmp;
		}
		else {
			if (lt(heap[M][cur],heap[M][cur / 2])) break;
			int tmp = heap[M][cur / 2];
			heap[M][cur / 2] = heap[M][cur];
			heap[M][cur] = tmp;
		}
	}
}

int pop(int M) {
	int ret = heap[M][1];
	heap[M][1] = heap[M][h_size[M]--];
	int child;
	for ( int cur = 1; cur * 2 <= h_size[M];) {
		if (cur * 2 == h_size[M]) {
			child = cur * 2;
		}
		else {
			if (M == 0) {
				if (lt(heap[M][cur * 2], heap[M][cur * 2 + 1])) child = cur * 2;
				else child = cur * 2 + 1;
			}
			else {
				if (lt(heap[M][cur * 2 + 1], heap[M][cur * 2])) child = cur * 2;
				else child = cur * 2 + 1;
			}
		}
		if (M == 0) {
			if (lt(heap[M][cur], heap[M][child])) break;
		}
		else if (M == 1) {
			if (lt(heap[M][child], heap[M][cur])) break;
		}
		int tmp = heap[M][cur];
		heap[M][cur] = heap[M][child];
		heap[M][child] = tmp;

		cur = child;
	}

	return ret;
}



int main(void) {
	int T, N, A, q1,q2, ans;
	scanf("%d", &T);
	for ( int tc = 1; tc <= T; tc++) {
		h_init(); ans = 0;
		scanf("%d %d", &N, &A);
		push(A, 1);
		for (int n = 0; n < N; n++) {
			scanf("%d %d", &q1, &q2);
			if (q1 > heap[1][1]) push(q1,0);
			else push(q1, 1);
			if (q2 > heap[1][1]) push(q2, 0);
			else push(q2, 1);
			if (h_size[1] < h_size[0]) push(pop(0), 1);
			else if (h_size[1] - 1 > h_size[0]) push(pop(1), 0);
			ans += heap[1][1];
			if (ans >= 20171109) ans %= 20171109;
		}
		
		printf("#%d %d\n", tc, ans);
	}

}
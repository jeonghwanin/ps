/*
더블 링크드 리스트, 개수
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
struct Node {
	Node* next;
	Node* prev;
	int id;	//선물 번호
};
Node node[100001];
int cnt[100001];
Node head[100001];
Node tail[100001];

int N, M;

void print(int n) {
	Node* ptr = &head[n];
	printf("belt %d(%d) : ", n, cnt[n]);
	while (ptr->next != &tail[n]) {
		ptr = ptr->next;
		printf("%d ", ptr->id);
	}
	printf("\n");
}

void init(void) {
	for (int t = 1; t <= N; ++t) {
		head[t].id = -1;
		tail[t].id = -1;
		head[t].next = &tail[t];
		tail[t].prev = &head[t];
	}
}

int carryAll(int m_src, int m_dst) {

	if (cnt[m_src] == 0) return cnt[m_dst];

	tail[m_src].prev->next = head[m_dst].next;
	head[m_dst].next->prev = tail[m_src].prev;
	head[m_dst].next = head[m_src].next;
	head[m_src].next->prev = &head[m_dst];

	if (cnt[m_dst] == 0) {

	}

	head[m_src].next = &tail[m_src];
	tail[m_src].prev = &head[m_src];
	
	cnt[m_dst] += cnt[m_src];
	cnt[m_src] = 0;

	return cnt[m_dst];
}

int changeFront(int m_src, int m_dst) {
	if (cnt[m_src] == 0 && cnt[m_dst] == 0) return cnt[m_dst];
	if (cnt[m_src] == 0) {
		--cnt[m_dst];
		++cnt[m_src];
		int id = head[m_dst].next->id;
		node[id].prev->next = node[id].next;
		node[id].next->prev = node[id].prev;

		node[id].next = &tail[m_src];
		node[id].prev = &head[m_src];
		head[m_src].next = &node[id];
		tail[m_src].prev = &node[id];

		return cnt[m_dst];
	}
	if (cnt[m_dst] == 0) {
		--cnt[m_src];
		++cnt[m_dst];
		int id = head[m_src].next->id;
		node[id].prev->next = node[id].next;
		node[id].next->prev = node[id].prev;

		node[id].next = &tail[m_dst];
		node[id].prev = &head[m_dst];
		head[m_dst].next = &node[id];
		tail[m_dst].prev = &node[id];

		return cnt[m_dst];
	}
	//둘다 0아닐때
	int id_src = head[m_src].next->id;
	int id_dst = head[m_dst].next->id;

	node[id_src].prev->next = node[id_src].next;
	node[id_src].next->prev = node[id_src].prev;

	node[id_dst].prev->next = node[id_dst].next;
	node[id_dst].next->prev = node[id_dst].prev;

	node[id_src].next = head[m_dst].next;
	node[id_src].prev = &head[m_dst];
	node[id_src].prev->next = &node[m_dst];
	node[id_src].next->prev = &node[m_dst];

	node[id_dst].next = head[m_src].next;
	node[id_dst].prev = &head[m_src];
	node[id_dst].prev->next = &node[m_src];
	node[id_dst].next->prev = &node[m_src];

	return cnt[m_dst];

}

int getNode(int id) {
	return node[id].prev->id + 2 * node[id].next->id;
}

int getMode(int id) {
	return head[id].next->id + 2 * tail[id].prev->id + 3*cnt[id];
}

int divide(int m_src, int m_dst) {
	int k = (cnt[m_src] / 2);
	if (k == 0) return cnt[m_dst];
	cnt[m_src] -= k;
	cnt[m_dst] += k;
	Node* ptr = &head[m_src];
	for (int t = 0; t < k; ++t) {
		ptr = ptr->next;
	}
	Node* tmp = ptr->next;

	ptr->next = head[m_dst].next;
	head[m_dst].next->prev = ptr;
	head[m_dst].next = head[m_src].next;
	head[m_src].next->prev = &head[m_dst];

	head[m_src].next = tmp;
	tmp->prev = &head[m_src];
	return cnt[m_dst];
}

int main(void) {
	
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int q, a, b,c,d;
	scanf(" %d", &q);
	scanf(" %d %d %d", &a, &N, &M);
	init();
	for (int t = 1; t <= M; ++t) {
		scanf(" %d", &a);
		++cnt[a];
		node[t].id = t;
		tail[a].prev->next = &node[t];
		node[t].prev = tail[a].prev;
		node[t].next = &tail[a];
		tail[a].prev = &node[t];
	}
	for (int t = 1; t <= N; ++t) {
		print(t);
	}
	for (int t = 1; t < q; ++t) {
		scanf( "%d", &a);
		if (a == 200) {
			scanf("%d %d", &b, &c);
			printf("%d\n",carryAll(b, c));
			for (int t = 1; t <= N; ++t) {
				print(t);
			}
		}
		else if (a == 300) {
			scanf( " %d %d", &b, &c);
			printf("%d\n", changeFront(b, c));
			for (int t = 1; t <= N; ++t) {
				print(t);
			}
		}
		else if (a == 400) {
			scanf(" %d %d", &b, &c);
			printf("%d\n", divide(b, c));
			for (int t = 1; t <= N; ++t) {
				print(t);
			}
		}
		else if (a == 500) {
			scanf(" %d", &b);
			printf("%d\n", getNode(b));
			for (int t = 1; t <= N; ++t) {
				print(t);
			}
		}
		else if (a == 600) {
			scanf(" %d", &b);
			printf("%d\n", getMode(b));
			for (int t = 1; t <= N; ++t) {
				print(t);
			}
		}
	}
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define LIST_SIZE  2000

struct Node {
	int data;
	Node* next;
};

Node list[LIST_SIZE];
int size;
Node head;
Node tail;
Node* new_node(int data)
{
	list[size] = { data, (Node*)0 };
	return &list[size++];
}

int main(void)
{
	//freopen("input.txt", "r", stdin);
	int T, N,M,L;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++)
	{
		scanf("%d %d %d", &N, &M, &L);

		//수열 입력
		size = 0;
		Node* ptr = &head;
		for (int t = 0; t < N; t++)
		{
			int data;
			scanf("%d", &data);
			ptr->next = new_node(data);
			ptr = ptr->next;
		}
		tail.next = ptr;

		for (int t = 0; t < M; t++)
		{
			char i;
			scanf(" %c", &i);
			if (i == 'I') {
				int index, data;
				scanf("%d %d", &index, &data);
				ptr = &head;
				for (int q = 0; q < index; q++)
				{
					ptr = ptr->next;
				}
				Node* tmp = new_node(data);
				if (ptr == tail.next)
				{
					ptr->next = tmp;
					tail.next = tmp;
				}
				else
				{
					tmp->next = ptr->next;
					ptr->next = tmp;
				}

			}
			else if (i == 'D') {
				int index;
				scanf("%d", &index);
				ptr = &head;
				for (int q = 0; q < index; q++)
				{
					ptr = ptr->next;
				}
				if (ptr->next == tail.next) {
					tail.next = ptr;
				}
				else ptr->next = ptr->next->next;

			}
			else if (i == 'C') {
				int index, data;
				scanf("%d %d", &index, &data);
				ptr = &head;
				for (int q = 0; q < index; q++)
				{
					ptr = ptr->next;
				}
				ptr = ptr->next;
				ptr->data = data;

			}
		}
		ptr = &head;
		bool finish = false;
		for (int t = 0; t <= L; t++)
		{
			if (ptr == tail.next) {
				printf("#%d %d\n", tc, -1);
				finish = true;
				break;
			}
			ptr = ptr->next;
		}
		if (!finish) {
			printf("#%d %d\n", tc, ptr->data);
		}
	}
}

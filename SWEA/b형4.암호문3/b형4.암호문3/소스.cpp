#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define SIZE 4000
struct Node {
	int data;
	Node* next;
};
Node list[100000];
int list_size;
Node head;
Node tail;

Node* new_node(int data)
{
	list[list_size] = { data, (Node*)0 };
	return &list[list_size++];
}

void intsert(int x)
{
	Node* node = new_node(x);
	node->next = head.next;
	head.next = node;
}

int main(void)
{
	int N,M;
	freopen("input.txt", "r", stdin);
	for (int tc = 1; tc <= 10; tc++)
	{
		list_size = 0;
		head.next = (Node*)0;
		tail.next = (Node*)0;
		scanf("%d", &N);

		Node* tmp = &head;
		for (int n = 0; n < N; n++)
		{
			int data;
			scanf("%d", &data);
			tmp->next = new_node(data);
			tmp = tmp->next;
		}
		tail.next = tmp;
		scanf("%d", &M);
		
		for (int m = 0; m < M; m++)
		{
			char i;
			scanf(" %c", &i);
			if (i == 'I')
			{
				int x,y;
				scanf("%d%d", &x, &y);
				Node* ptr = &head;
				for (int t=0; t<x; t++)
				{
					ptr = ptr->next;
				}
				Node* tmp2 = ptr->next;
				for (int t = 0; t < y; t++)
				{
					int k;
					
					scanf("%d", &k);
					ptr->next = new_node(k);
					ptr = ptr->next;				
				}
				if (tmp2 == tail.next)
				{
					tail.next = ptr;
				}
				else ptr->next = tmp2;
			}
			else if (i == 'D')
			{
				int x, y;
				scanf("%d%d", &x, &y);
				Node* ptr = &head;
				for (int t = 0; t < x; t++)
				{
					ptr = ptr->next;
				}
				Node* tmp2 = ptr;
				for (int t = 0; t < y; t++) tmp2 = tmp2->next;
				if (tmp2 == tail.next)
				{
					ptr->next = (Node*)0;
					tail.next = ptr;
				}
				else ptr->next = tmp2->next;
			}
			else if (i == 'A')
			{
				int y;
				scanf("%d", &y);
				Node* ptr = tail.next;
				for (int t = 0; t < y; t++)
				{
					int k;
					scanf("%d", &k);
					ptr->next = new_node(k);
					ptr = ptr->next;
				}
				tail.next = ptr;
			}
		}

		printf("#%d ", tc);
		Node* ptr = &head;
		for (int t = 0; t < 10; t++)
		{
			ptr = ptr->next;
			printf("%d ", ptr->data);
		}
		printf("\n");
	}

}

/*
3
1 2 3
3 I 1 10 0 0 0 0 0 0 0 0 0 0 A 5 1 2 3 4 5 D 1 7
*/
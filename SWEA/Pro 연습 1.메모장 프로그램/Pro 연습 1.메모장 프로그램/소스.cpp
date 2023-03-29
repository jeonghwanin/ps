int alpa_cnt[301][26];//indexÇàÀÇ °¢°¢ ¾ËÆÄºª ÃÑ °³¼ö
int MAXW;//³Êºñ
struct Node {
	char c;
	Node* next;
 };// ¾ËÆÄºª
Node head[301]; //°¢ Çà¸¶´Ù ¾ËÆÄºª ¼ø¼­
Node tail
Node* cursor;
int cursor_row;
Node pool[90000];
int size; // ¾ËÆÄ¹î ÃÑ °³¼ö

Node* new_pool(char c) {
	pool[size] = { c, 0 };
	return &pool[size++];
}

int get_row(void) {
	return size / MAXW + 1;
}

void init(int H, int W, char mStr[])
{
	cursor = &head[1];
	cursor_row = 1;
	size = 0;
	MAXW = W;
	for (int y = 1; y <= H; ++y) {
		for (int x = 0; x < 26; ++x) {
			alpa_cnt[y][x] = 0;
		}
		head[y].next = 0;
	}
	int p = 1;
	Node* ptr = &head[p];
	for (int t = 0; mStr[t]; ++t) {
		ptr->next = new_pool(mStr[t]);
		++alpa_cnt[p][mStr[t] - 'a'];
		ptr = ptr->next;
		if (p < size / MAXW + 1) {
			p = size / MAXW + 1;
			ptr = &head[p];
		}
	}
}

void insert(char mChar)
{
	if (cursor_row < get_row()) {

	}
	else if (cursor_row == get_row()){

	}
	else {
		Node* New = new_pool(mChar);
		New->next = cursor->next;
		cursor->next = New;
		cursor = New;
		++alpa_cnt[cursor_row][mChar - 'a'];
	}
}

char moveCursor(int mRow, int mCol)
{
	return '$';
}

int countCharacter(char mChar)
{
	return -1;
}

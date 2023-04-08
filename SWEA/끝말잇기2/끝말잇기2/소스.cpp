#define MAX_N 50000
#define MAX_TABLE (10007)
#define MAX_M 50000
#define MAX_LEN 11
// 플레이어 링크드 리스트
struct Node {
	int id;
	Node* prev;
	Node* next;
};
Node p[MAX_N + 1];
int cnt;
// 해시 테이블
struct Word {
	char s[11];
	Word* next;
};
Word hash_table[MAX_TABLE];
Word db[100000];
int db_size;

void scp(char* a, const char* b) {
	while (*a++ = *b++);
}

int scmp(const char* a, const char* b) {
	while (*a && *a == *b) ++a, ++b;
	return *a - *b;
}

unsigned long long hash(const char* str)
{
	unsigned long long int hash = 5381;
	int c;

	while (c = *str++)
	{
		hash = (((hash << 5) + hash) + c) % MAX_TABLE;
	}

	return hash % MAX_TABLE;
}
void h_push(unsigned long long h, char* s) {
	Word* n = &db[db_size++];
	scp(n->s, s);

	n->next = hash_table[h].next;
	hash_table[h].next = n;
}

bool add(char* s) {
	unsigned long long h = hash(s);

	for (Word* ptr = hash_table[h].next; ptr; ptr = ptr->next) {
		if (!scmp(ptr->s, s)) {
			return false;
		}
	}
	h_push(h, s);
	return true;
}


// 사용한 문자열
char str[50001][11];
int str_size;
char last;
// 트라이
struct Trie {
	bool t;
	int size;
	Trie* prev;
	Trie* child[26];
};
Trie pool[1100010];
Trie root;
int p_size;

// 트라이 노드 생성
Trie* new_pool(void) {
	pool[p_size].t = false;
	pool[p_size].size = 0;
	pool[p_size].prev = 0;
	for (int t = 0; t < 26; t++)
		pool[p_size].child[t] = 0;

	return &pool[p_size++];
}
// 트라이 문자열 넣기
void push(char* s) {
	Trie* ptr = &root;
	ptr->size++;
	while (*s != 0) {
		if (ptr->child[*s - 'a'] == 0) {
			ptr->child[*s - 'a'] = new_pool();
			ptr->child[*s - 'a']->prev = ptr;
		}

		ptr = ptr->child[*s - 'a'];
		++ptr->size;
		++s;
	}
	if (ptr->t == true) {
		while (ptr != &root) {
			--ptr->size;
			ptr = ptr->prev;
		}
		--ptr->size;
	}
	else ptr->t = true;
}
// 트라이 문자열 제거
bool pop(char a) {
	Trie* ptr = &root;
	if (ptr->child[a - 'a'] == 0 || ptr->child[a - 'a']->size == 0) return false;
	--ptr->size;
	ptr = ptr->child[a - 'a'];
	--ptr->size;
	int index = 0;
	str[str_size][index++] = a;
	while (ptr->t != true) {
		for (int t = 0; t < 26; t++) {
			if (ptr->child[t] != 0 && ptr->child[t]->size > 0) {
				ptr = ptr->child[t];
				str[str_size][index++] = t + 'a';
				break;
			}
		}
		--ptr->size;
	}
	last = str[str_size][index - 1];
	str[str_size][index] = '\0';
	char cpstr[11];
	for (int t = 0; t < index; t++) {
		cpstr[t] = str[str_size][index - 1 - t];
	}
	for (int t = 0; t < index; t++) {
		str[str_size][t] = cpstr[t];
	}
	++str_size;
	ptr->t = false;
	return true;
}

void init(int N, int M, char mWords[][MAX_LEN]) {

	db_size = 0;
	p_size = 0;
	for (int t = 0; t < MAX_TABLE; t++) {
		hash_table[t].next = 0;
	}
	root.size = 0;
	cnt = N;
	for (int t = 0; t < 26; t++)
		root.child[t] = 0;
	p[1].id = 1;
	for (int t = 1; t <= cnt; t++) {
		if (t == cnt) {
			p[t].next = &p[1];
			p[1].prev = &p[t];
		}
		else {
			p[t + 1].id = t + 1;
			p[t].next = &p[t + 1];
			p[t + 1].prev = &p[t];
		}

	}

	for (int t = 0; t < M; t++) {
		push(mWords[t]);
		h_push(hash(mWords[t]), mWords[t]);
	}

}

int playRound(int mID, char mCh) {
	last = mCh;

	str_size = 0;
	Node* ptr = &p[mID];
	if (ptr == ptr->next) return ptr->id;
	while (pop(last)) {

		ptr = ptr->next;

	}
	ptr->prev->next = ptr->next;
	ptr->next->prev = ptr->prev;

	for (int t = 0; t < str_size; t++) {
		if (add(str[t])) push(str[t]);
	}

	return ptr->id;
}


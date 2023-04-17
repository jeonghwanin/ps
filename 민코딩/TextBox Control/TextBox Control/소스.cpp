// *** user.cpp ***
struct Node {
    Node* next;
    Node* prev;
    char c;
};
Node pool[120000];
int cnt;
int row_cnt[300];
int cursor_row;
Node* cursor;
Node head[100];
Node tail[100];
// letter_cnt[i][j] : i행의 j+'a' 문자의 개수
int letter_cnt[300][26];
int h_max;
int w_max;
void init(int H, int W, char initStr[]) {
    // 문자 개수 초기화
    cnt = 0;
    // 검색 사각형 초기화
    h_max = H;
    w_max = W;
    // 이중연결리스트 초기화
    for (int i = 0; i < H; ++i) {
        head[i].next = &tail[i];
        tail[i].prev = &head[i];
        row_cnt[i] = 0;
    }
    // 각 행별 문자별개수 초기화
    for(int j=0; j < h_max; j++)
    {
        for (int i = 0; i <= 26; ++i) {
            letter_cnt[j][i] = 0;
        }
    }
    // 이중연결리스트 채우기
    int j = 0;
    for (int i = 0; i < sizeof(initStr); ++i) {
        pool[cnt] = { 0,0,initStr[i] };
        pool[cnt].next = head[j].next;
        pool[cnt].prev = &head[j];
        pool[cnt].next->prev = &pool[cnt];
        pool[cnt].prev->next = &pool[cnt];
        ++cnt;
        ++letter_cnt[j][initStr[i] - 'a'];
        row_cnt[j]++;
        if (i % w_max == 0) {
            ++j;
        }
    }
    //커서 위치 결정
    cursor = head[0].next;
    cursor_row = 0;
}
void insertChar(char ch) {



    pool[cnt] = { 0,0,ch };
    pool[cnt].next = cursor;
    pool[cnt].prev = cursor->prev;
    pool[cnt].next->prev = &pool[cnt];
    pool[cnt].prev->next = &pool[cnt];
    ++letter_cnt[cursor_row][ch - 'a'];
    
    if (row_cnt[cursor_row] == w_max) {
        if (cursor == &tail[cursor_row])
        {
            cursor = head[cursor_row + 1].next;
            ++cursor_row;
        }
        
    }
    else {
        
    }

    cnt++;
    return;
}
char moveCursor(int mr, int mc) {
    return '$';
}
int countChar(char ch) {
    return 0;
}
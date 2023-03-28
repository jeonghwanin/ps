#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;
struct Node {
	int size; //오타 개수
	char str[5][11]; //
	int cnt[5];
};
struct Person {
	int last;
	char str[11];
};

unordered_map<string, Node>LOG; //오타 후보 기록
unordered_map<string, string>DB; //오타 교정 DB
Person p[2001];

// The below commented functions are for your reference. If you want 
// to use it, uncomment these functions.
/*
int mstrcmp(const char *a, const char *b)
{
	int i;
	for (i = 0; a[i] != '\0'; i++)
	{
		if (a[i] != b[i])
			return a[i] - b[i];
	}
	return a[i] - b[i];
}

int mstrncmp(const char *a, const char *b, int len)
{
	for (int i = 0; i < len; i++)
	{
		if (a[i] != b[i])
			return a[i] - b[i];
	}
	return 0;
}

int mstrlen(const char *a)
{
	int len = 0;

	while (a[len] != '\0')
		len++;

	return len;
}

void mstrcpy(char *dest, const char *src)
{
	int i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = src[i];
}

void mstrncpy(char *dest, const char *src, int len)
{
	for (int i = 0; i<len; i++)
	{
		dest[i] = src[i];
	}
	dest[len] = '\0';
}
*/

void init(int n) {
	LOG.clear();
	DB.clear();
	for (int t = 1; t <= 2000; ++t) p[t].last = -11;
}

int search(int mId, int searchTimestamp, char searchWord[11], char correctWord[5][11]) {
	// 최근 검색이 있는지 확인하기
	if (searchTimestamp - p[mId].last <= 10) {
		//유형 확인
	}
	else {

	}
	return 0;
}
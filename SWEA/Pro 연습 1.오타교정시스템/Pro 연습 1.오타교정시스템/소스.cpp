#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

struct Person {
	int last;
	string str;
};

unordered_map<string, int>LOG; //��Ÿ �ĺ� ���
unordered_map<string, string>DB[5]; //��Ÿ ���� DB
unordered_map<string, int>DB_CNT;// ��Ÿ ���� DB ����
Person p[2001];


void init(int n) {
	LOG.clear();
	for(int t=0; t<5; ++t) DB[t].clear();
	DB_CNT.clear();
	for (int t = 1; t <= n; ++t) p[t].last = -11;
}

int search(int mId, int searchTimestamp, char searchWord[11], char correctWord[5][11]) {
	// �ֱ� �˻��� �ִ��� Ȯ���ϱ�
	string s = searchWord;
	if (searchTimestamp - p[mId].last <= 10) {
		//���� Ȯ��
		int prevLen = p[mId].str.length();
		int nowLen = s.length();
		bool find = true;
		if (prevLen == nowLen) {
			//��Ÿ ���� ġȯ Ȯ��
			int cnt = 0;
			for (int t = 0; t < prevLen; ++t) {
				if (p[mId].str[t] != searchWord[t]) {
					++cnt;
					if (cnt > 1) {
						find = false;
						break;
					}
				}
			}
		}
		else if (prevLen == nowLen + 1) {
			//��Ÿ ���� ���� Ȯ��
			int cnt = 0;
			int a = 0;
			for (int t = 0; t < prevLen; ++t, ++a) {
				if (p[mId].str[t] != searchWord[a]) {
					--t;
					++cnt;
				}
				if (cnt > 1) {
					find = false;
					break;
				}
			}
		}
		else if (prevLen == nowLen - 1) {
			//��Ÿ ���� �߰� Ȯ��
			int cnt = 0;
			int a = 0;
			for (int t = 0; t < nowLen; ++t, ++a) {
				if (p[mId].str[a] != searchWord[t]) {
					--t;
					++cnt;
				}
				if (cnt > 1) {
					find = false;
					break;
				}
			}
		}
		//��Ÿ �ĺ��� ���
		string str = p[mId].str + '+' + s;

		if (find) {
			if (LOG[str] < 3) {
				++LOG[str];
				if (LOG[str] == 3) {
					//��Ÿ ���� DB ���
					DB[DB_CNT[p[mId].str]][p[mId].str] = s;
					++DB_CNT[p[mId].str];
				}
			}
		}

		p[mId].str = s;
		p[mId].last = searchTimestamp;
		return 0;
	}
	else {
		int n = DB_CNT[s];
		for (int t = 0; t < n; ++t) {
			string tmp = DB[t][s];
			int q;
			for (q = 0; q < tmp.length(); ++q) {
				correctWord[t][q] = tmp[q];
			}
			correctWord[t][q] = '\0';
		}
		p[mId].str = s;
		p[mId].last = searchTimestamp;
		return n;
	}
}
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <cstring>
using namespace std;

struct Person {
	int last;
	string str;
};

int d_cnt;

unordered_map<string, int>LOG; //오타 후보 기록
unordered_map<string, string>DB[5]; //오타 교정 DB
unordered_map<string, int>DB_CNT;// 오타 교정 DB 개수
unordered_set<string>visited; //오타 후보 중복제거
Person p[2001];


void init(int n) {
	d_cnt = 0;
	LOG.clear();
	for(int t=0; t<5; ++t) DB[t].clear();
	DB_CNT.clear();
	visited.clear();
	for (int t = 1; t <= n; ++t) p[t].last = -11;
}

int search(int mId, int searchTimestamp, char searchWord[11], char correctWord[5][11]) {
	//printf("num: %d T:%d id: %d  %s\n",++d_cnt,searchTimestamp, mId, searchWord);
	// 최근 검색이 있는지 확인하기
	if (++d_cnt == 12804) {
		int d = 0;
	}
	string s = searchWord;
	if (searchTimestamp - p[mId].last <= 10) {
		//유형 확인
		int prevLen = p[mId].str.length();
		int nowLen = s.length();
		bool find = true;
		if (prevLen == nowLen) {
			//오타 유형 치환 확인
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
			if (cnt == 0) find = false;
		}
		else if (prevLen == nowLen - 1) {
			//오타 유형 삭제 확인
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
		else if (prevLen == nowLen + 1) {
			//오타 유형 추가 확인
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
		//오타 후보 중복확인
		
	
		string str_visited = p[mId].str + s + to_string(mId);
		if (visited.find(str_visited) == visited.end()) {
			visited.insert(str_visited);
		}
		else {
			find = false;
		}
		
		//오타 후보 가능하면 등록
		string str = p[mId].str + '+' + s;

		if (find) {
			if (LOG[str] < 3) {
				++LOG[str];
				if (LOG[str] == 3) {
					//오타 교정 DB 등록
					DB[DB_CNT[p[mId].str]][p[mId].str] = s;
					++DB_CNT[p[mId].str];
				}

			}
		}

		p[mId].str = s;
		p[mId].last = searchTimestamp;
		
	}

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
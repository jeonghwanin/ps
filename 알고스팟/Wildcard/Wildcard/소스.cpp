#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <iostream>
#include <cstring>
using namespace std;
int N;
int cnt;
string W;
string S;
string ans[50];
string tmp[50];
int cache[101][101];

bool match(int w, int s) {
	int& ret = cache[w][s];

	if (ret != -1) return ret;

	if(s < S.size() && w < W.size() &&
		(W[w] == '?' || W[w] == S[s])) {
		return ret = match(w + 1, s + 1);
	}
	if (w == W.size()) return ret = (s == S.size());
	if (W[w] == '*') {
		if (match(w + 1, s ) || (s < S.size() && match(w, s + 1))) return ret = 1;
	}
	return ret = 0;
}

void sort(int left, int right) {
	if (left == right) return;
	int i = left;
	int mid = (left + right) / 2;
	int j = mid + 1;
	int k = 0;
	while (i <= mid && j <= right) {
		if (ans[i] <= ans[j]) tmp[k++] = ans[i++];
		else tmp[k++] = ans[j++];
	}
	while (i <= mid) {
		tmp[k++] = ans[i++];
	}
	while (j <= right) {
		tmp[k++] = ans[j++];
	}
	for (int i = left; i <= right; ++i) {
		ans[i] = tmp[i - left];
	}
}

void merge(int left, int right) {
	if (left == right) return;
	int mid = (left + right) / 2;
	merge(left, mid);
	merge(mid + 1, right);
	sort(left, right);
}

int main(void) {
	int C;
	cin >>C;
	
	for (int c = 0; c < C; ++c) {
		cin >> W;
		cin >> N;
		cnt = 0;
		for (int n = 0; n < N; ++n) {
			cin >> S;
			memset(cache, -1, sizeof(cache));
			if (match(0, 0)) {
				ans[cnt++] = S;
			}
		}
		if(cnt  != 0) merge(0, cnt - 1);
		
		for (int t = 0; t < cnt; ++t) {
			cout << ans[t] << '\n';
		}
	}
}
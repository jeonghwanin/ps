#include <iostream>
#include <string>
#include <set>
using namespace std;
int main(void) {
	int T, K;
	string str;
	set<string>s;
	cin >> T;
	for (int tc = 1; tc <= T; ++tc) {
		cin >> K >> str;
		s.clear();
		for (int y = 0; y < str.length(); ++y)
			for (int x = 1; x <= str.length(); ++x) {
				s.insert(str.substr(y, x));
			}
		set<string>::iterator it = s.begin();

		if(s.size() < K)cout << '#' << tc << ' ' << "none\n";
		else {
			for (int t = 1; t < K; ++t) {
				++it;
			}
			cout << '#' << tc << ' ' << *it << '\n';
		}

	}
}
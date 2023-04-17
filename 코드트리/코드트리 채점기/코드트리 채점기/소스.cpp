#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <queue>

using namespace std;




//domain id creater
int id;
unordered_map<string, int>domainId;
// url , waiting set
unordered_set<int>waitingS[301];
struct  Node {
	int gid;	//도메인 아이디
	int nid;	//문제목록 id
	int prio;
	int t;
};
struct cmp {
	bool operator()(Node c, Node p) {
		if (c.prio > p.prio) return true;
		if (c.prio < p.prio) return false;
		if (c.t > p.t) return true;
		if (c.t < p.t) return false;
		return false;
	}
};
priority_queue<Node, vector<Node>, cmp>domainPq[301];
// url , in the process of grading
int process[301];
// 채점 대기 큐 개수
int cnt;
// 채점 최소 시간
int last_time[301];
// robot priority_queue
priority_queue<int, vector<int>, greater<int>>Robot;
struct Node2 {
	//string url;
	int id;
	int initial_time;
};
// index id 로봇이 채점중인 url과 채점 시작 시간을 저장하는 변수
Node2 RobotUrl[50001];
struct Node3 {
	int gid;
	int nid;
};
Node3 getDomainId(string s) {
	//"/"을 통해 도메인을 구한다.
	int pos=0;
	while (1) {
		if (s[pos] == '/') break;
		++pos;
	}
	string domain = s.substr(0, pos);
	string num = s.substr(pos+1, s.length()-pos);
	//도메인의 id가 존재하지 않는다면 새로운 id를 만들어 리턴한다.
	if (domainId.find(domain) == domainId.end()) {
		domainId.insert({ domain, ++id });
		return { id, stoi(num)};
	}
	//도메인의 id가 존재하면 리턴한다.
	else {
		return { domainId[domain], stoi(num)};
	}
}

void init(int N, string url) {
	// 초기화
	//reserve
	// 로봇 N개를 robot 우선순위 큐에 등록함
	for (int t = 1; t <= N; ++t) {
		Robot.push(t);
	}
	// 처음 url은 아무 조건 없이 무조건 추가됨
	Node3 now = getDomainId(url);
	waitingS[now.gid].insert(now.nid);
	// 처음 url의  채점 우선순위는 1이면서 시간은 0임
	// 처음 url의 도메인 id를 구해 우선순위 큐에 등록
	domainPq[now.gid].push({now.gid, now.nid,1,0});
	//waiting q 개수를 1 증가
	++cnt;
}

void add(int time, int prio, string url) {
	// 만약 waiting q에 똑같은 url이 존재한다면 추가 못함
	Node3 now = getDomainId(url);
	if (waitingS[now.gid].find(now.nid) != waitingS[now.gid].end()) {
		//printf("추가 못함\n");
		return;
	}
	// 똑같은 url이 없으므로 등록함
	waitingS[now.gid].insert(now.nid);
	// url의 도메인 Id를 구한 후 우선순위 큐에 삽입
	domainPq[now.gid].push({ now.gid, now.nid, prio, time });
	// waiting q 개수를 1 증가
	++cnt;
	return;
}

void order(int time) {

	// 대기 큐에 없으면 채점 못함
	if (cnt == 0) {
		return;
	}
	// 현재 쉬는 로봇이 없으면 채점 못해
	if (Robot.empty()) {
		//printf("채점 못함\n");
		return;
	}
	// 가장 낮은 우선순위와 가장 나중에 들어온 유령 url
	int prio = 21e8;
	int t = 1000001;
	int ID;
	int NID;
	// 지금까지 등록한 도메인 id들을 탐색함.
	for (int q = 1; q <= id; q++) {
		// 우선순위 큐에 없으면 넘어감
		if (domainPq[q].empty()) continue;
		//존재하면 검사함
		Node now = domainPq[q].top();

		//현재 채점중인 도메인이면 채점 불가
		if (process[now.gid] == 1) continue;
		// 현재 시간이 start+3*gap보다 작으면 채점 불가
		if (time < last_time[now.gid]) continue;
		// 두 조건을 통과하면 예상 url과 우선순위를 비교함
		if (now.prio < prio || (now.prio == prio && now.t <t) ){
			prio = now.prio;
			t = now.t;
			ID = now.gid;
			NID = now.nid;
		}
	}
	if (t == 1000001) {
		//없음
		//printf("채점 할게 없엉\n");
		return;
	}
	else {
		// 채점할 로봇을 구함
		int RobotId = Robot.top(); Robot.pop();
		// 채점할 url의 도메인 id를 구함
		//int ID = getDomainId(url);
		// 로봇에 등록함
		RobotUrl[RobotId] = { ID, time };
		// 도메인 채점중 기록
		process[ID] = 1;
		// 우선순위 큐에서 제거
		domainPq[ID].pop();
		// 채점 대기 큐 개수 1 감소
		--cnt;
		// 채점 대기 큐에서 삭제
		waitingS[ID].erase(NID);
	}
}

void end(int time, int robotId) {
	// 로봇 id를 통해 로봇이 채점하고 있지 않으면 리턴
	if (RobotUrl[robotId].id == 0) {
		//printf("채점 종료 못함\n");
		return;
	}
	// 채점하고 있으면 채점하는 url과 초기 시간을 구함
	Node2 endNode2 = RobotUrl[robotId];
	// 채점 완료 url의 도메인 id를 구함
	int ID = RobotUrl[robotId].id;
	// 채점이 완료 되었으니 삭제함
	RobotUrl[robotId].id = 0;
	
	// 도메인이 채점 안하고 있다고 기록
	process[ID] = 0;
	// 도메인 제한 시간을 수정함
	last_time[ID] = endNode2.initial_time + 3 * (time - endNode2.initial_time);
	//cout<< endNode2.url<<' '<< last_time[ID]<<'\n';
	// 로봇을 쉬게함
	Robot.push(robotId);
}

int main(void) {
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int Q;
	cin >> Q;
	int a, b;
	string s;
	for (int t = 0; t < Q; ++t) {
		cin >> a;
		if (a == 100) {
			cin >> b >> s;
			init(b, s);
		}
		else if (a == 200) {
			cin >> a >> b >> s;
			add(a, b, s);
		}
		else if (a == 300) {
			cin >> b;
			order(b);
		}
		else if (a == 400) {
			cin >> a >> b;
			end(a, b);
		}
		else if (a == 500) {
			cin >> b;
			cout << cnt << '\n';
		}
	}
}
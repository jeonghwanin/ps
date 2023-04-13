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
	int gid;	//������ ���̵�
	int nid;	//������� id
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
// ä�� ��� ť ����
int cnt;
// ä�� �ּ� �ð�
int last_time[301];
// robot priority_queue
priority_queue<int, vector<int>, greater<int>>Robot;
struct Node2 {
	//string url;
	int id;
	int initial_time;
};
// index id �κ��� ä������ url�� ä�� ���� �ð��� �����ϴ� ����
Node2 RobotUrl[50001];
struct Node3 {
	int gid;
	int nid;
};
Node3 getDomainId(string s) {
	//"/"�� ���� �������� ���Ѵ�.
	int pos=0;
	while (1) {
		if (s[pos] == '/') break;
		++pos;
	}
	string domain = s.substr(0, pos);
	string num = s.substr(pos+1, s.length()-pos);
	//�������� id�� �������� �ʴ´ٸ� ���ο� id�� ����� �����Ѵ�.
	if (domainId.find(domain) == domainId.end()) {
		domainId.insert({ domain, ++id });
		return { id, stoi(num)};
	}
	//�������� id�� �����ϸ� �����Ѵ�.
	else {
		return { domainId[domain], stoi(num)};
	}
}

void init(int N, string url) {
	// �ʱ�ȭ
	//reserve
	// �κ� N���� robot �켱���� ť�� �����
	for (int t = 1; t <= N; ++t) {
		Robot.push(t);
	}
	// ó�� url�� �ƹ� ���� ���� ������ �߰���
	Node3 now = getDomainId(url);
	waitingS[now.gid].insert(now.nid);
	// ó�� url��  ä�� �켱������ 1�̸鼭 �ð��� 0��
	// ó�� url�� ������ id�� ���� �켱���� ť�� ���
	domainPq[now.gid].push({now.gid, now.nid,1,0});
	//waiting q ������ 1 ����
	++cnt;
}

void add(int time, int prio, string url) {
	// ���� waiting q�� �Ȱ��� url�� �����Ѵٸ� �߰� ����
	Node3 now = getDomainId(url);
	if (waitingS[now.gid].find(now.nid) != waitingS[now.gid].end()) {
		//printf("�߰� ����\n");
		return;
	}
	// �Ȱ��� url�� �����Ƿ� �����
	waitingS[now.gid].insert(now.nid);
	// url�� ������ Id�� ���� �� �켱���� ť�� ����
	domainPq[now.gid].push({ now.gid, now.nid, prio, time });
	// waiting q ������ 1 ����
	++cnt;
	return;
}

void order(int time) {

	// ��� ť�� ������ ä�� ����
	if (cnt == 0) {
		return;
	}
	// ���� ���� �κ��� ������ ä�� ����
	if (Robot.empty()) {
		//printf("ä�� ����\n");
		return;
	}
	// ���� ���� �켱������ ���� ���߿� ���� ���� url
	int prio = 21e8;
	int t = 1000001;
	int ID;
	int NID;
	// ���ݱ��� ����� ������ id���� Ž����.
	for (int q = 1; q <= id; q++) {
		// �켱���� ť�� ������ �Ѿ
		if (domainPq[q].empty()) continue;
		//�����ϸ� �˻���
		Node now = domainPq[q].top();

		//���� ä������ �������̸� ä�� �Ұ�
		if (process[now.gid] == 1) continue;
		// ���� �ð��� start+3*gap���� ������ ä�� �Ұ�
		if (time < last_time[now.gid]) continue;
		// �� ������ ����ϸ� ���� url�� �켱������ ����
		if (now.prio < prio || (now.prio == prio && now.t <t) ){
			prio = now.prio;
			t = now.t;
			ID = now.gid;
			NID = now.nid;
		}
	}
	if (t == 1000001) {
		//����
		//printf("ä�� �Ұ� ����\n");
		return;
	}
	else {
		// ä���� �κ��� ����
		int RobotId = Robot.top(); Robot.pop();
		// ä���� url�� ������ id�� ����
		//int ID = getDomainId(url);
		// �κ��� �����
		RobotUrl[RobotId] = { ID, time };
		// ������ ä���� ���
		process[ID] = 1;
		// �켱���� ť���� ����
		domainPq[ID].pop();
		// ä�� ��� ť ���� 1 ����
		--cnt;
		// ä�� ��� ť���� ����
		waitingS[ID].erase(NID);
	}
}

void end(int time, int robotId) {
	// �κ� id�� ���� �κ��� ä���ϰ� ���� ������ ����
	if (RobotUrl[robotId].id == 0) {
		//printf("ä�� ���� ����\n");
		return;
	}
	// ä���ϰ� ������ ä���ϴ� url�� �ʱ� �ð��� ����
	Node2 endNode2 = RobotUrl[robotId];
	// ä�� �Ϸ� url�� ������ id�� ����
	int ID = RobotUrl[robotId].id;
	// ä���� �Ϸ� �Ǿ����� ������
	RobotUrl[robotId].id = 0;
	
	// �������� ä�� ���ϰ� �ִٰ� ���
	process[ID] = 0;
	// ������ ���� �ð��� ������
	last_time[ID] = endNode2.initial_time + 3 * (time - endNode2.initial_time);
	//cout<< endNode2.url<<' '<< last_time[ID]<<'\n';
	// �κ��� ������
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
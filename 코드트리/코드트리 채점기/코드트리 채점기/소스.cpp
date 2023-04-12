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
unordered_set<string>waitingS;
struct  Node {
	string url;
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
	string url;
	int initial_time;
};
// index id �κ��� ä������ url�� ä�� ���� �ð��� �����ϴ� ����
Node2 RobotUrl[50001];

int getDomainId(string s) {
	//"/"�� ���� �������� ���Ѵ�.
	string domain = s.substr(0, s.find("/"));
	//�������� id�� �������� �ʴ´ٸ� ���ο� id�� ����� �����Ѵ�.
	if (domainId.find(domain) == domainId.end()) {
		domainId.insert({ domain, ++id });
		return id;
	}
	//�������� id�� �����ϸ� �����Ѵ�.
	else {
		return domainId[domain];
	}
}

void init(int N, string url) {
	// �κ� N���� robot �켱���� ť�� �����
	for (int t = 1; t <= N; ++t) {
		Robot.push(t);
	}
	// ó�� url�� �ƹ� ���� ���� ������ �߰���
	waitingS.insert(url);
	// ó�� url��  ä�� �켱������ 1�̸鼭 �ð��� 0��
	// ó�� url�� ������ id�� ���� �켱���� ť�� ���
	domainPq[getDomainId(url)].push({url,1,0});
	//waiting q ������ 1 ����
	++cnt;
}

void add(int time, int prio, string url) {
	// ���� waiting q�� �Ȱ��� url�� �����Ѵٸ� �߰� ����
	if (waitingS.find(url) != waitingS.end()) {
		//printf("�߰� ����\n");
		return;
	}
	// �Ȱ��� url�� �����Ƿ� �����
	waitingS.insert(url);
	// url�� ������ Id�� ���� �� �켱���� ť�� ����
	int Id = getDomainId(url);
	domainPq[Id].push({ url, prio, time });
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
	string url;
	// ���ݱ��� ����� ������ id���� Ž����.
	for (int q = 1; q <= id; q++) {
		// �켱���� ť�� ������ �Ѿ
		if (domainPq[q].empty()) continue;
		//�����ϸ� �˻���
		Node now = domainPq[q].top();
		int Id = getDomainId(now.url);
		//���� ä������ �������̸� ä�� �Ұ�
		if (process[Id] == 1) continue;
		// ���� �ð��� start+3*gap���� ������ ä�� �Ұ�
		if (time < last_time[Id]) continue;
		// �� ������ ����ϸ� ���� url�� �켱������ ����
		if (now.prio < prio || (now.prio == prio && now.t <t) ){
			prio = now.prio;
			t = now.t;
			url = now.url;
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
		int ID = getDomainId(url);
		// �κ��� �����
		RobotUrl[RobotId] = { url, time };
		// ������ ä���� ���
		process[ID] = 1;
		// �켱���� ť���� ����
		domainPq[ID].pop();
		// ä�� ��� ť ���� 1 ����
		--cnt;
		// ä�� ��� ť���� ����
		waitingS.erase(url);
	}
}

void end(int time, int robotId) {
	// �κ� id�� ���� �κ��� ä���ϰ� ���� ������ ����
	if (RobotUrl[robotId].url.empty()) {
		//printf("ä�� ���� ����\n");
		return;
	}
	// ä���ϰ� ������ ä���ϴ� url�� �ʱ� �ð��� ����
	Node2 endNode2 = RobotUrl[robotId];
	// ä���� �Ϸ� �Ǿ����� ������
	RobotUrl[robotId].url.clear();
	// ä�� �Ϸ� url�� ������ id�� ����
	int ID = getDomainId(endNode2.url);
	// �������� ä�� ���ϰ� �ִٰ� ���
	process[ID] = 0;
	// ������ ���� �ð��� ������
	last_time[ID] = endNode2.initial_time + 3 * (time - endNode2.initial_time);
	//cout<< endNode2.url<<' '<< last_time[ID]<<'\n';
	// �κ��� ������
	Robot.push(robotId);
}

int main(void) {
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
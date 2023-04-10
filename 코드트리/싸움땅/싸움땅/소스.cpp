/*
나이브 하게 풀면 시간복잡도 O(n*k) = O(20 * 500)
총의 개수 n^2 - m (상한 399개)
격자의 각 칸마다 우선 순위 큐(총기), 존재 사람 정보
사람 포인트, 및 초기 공력력 권총 공격력
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <queue>
using namespace  std;
struct Map {
	int playerId; // 0이면 없음
	priority_queue<int> gun_pq;// 총 우선순위 큐
}map[21][21];
struct Player {
	int dir;// 플레이어 방향
	int y;	//플레이어 y좌표
	int x;	//플레이어 x좌표
	int initial_attack;	//초기 공격력
	int gun_attack;	//권총 공격력
	int point; //플레이어 포인트
}player[31];
struct Node {
	int y;
	int x;
};
int n, m, k, i;
int direct[4][2] = { -1,0,0,1,1,0,0,-1 };

Node move(int id) {
	map[player[id].y][player[id].x].playerId = 0;
	int dy = player[id].y + direct[player[id].dir][0];
	int dx = player[id].x + direct[player[id].dir][1];
	if (dy <= 0 || dy > n || dx <= 0 || dx > n)
	{
		player[id].dir = (player[id].dir + 2) % 4;
		dy = player[id].y + direct[player[id].dir][0];
		dx = player[id].x + direct[player[id].dir][1];
	}
	player[id].y = dy;
	player[id].x = dx;
	return { dy, dx };
}

void getGun(int id) {
	// 맵에 총이 있고 총의 공격력이 플레이어가 가진 총의 공격력 보다 크다면
	if (!map[player[id].y][player[id].x].gun_pq.empty() && player[id].gun_attack < map[player[id].y][player[id].x].gun_pq.top()) {
		map[player[id].y][player[id].x].gun_pq.push(player[id].gun_attack);
		player[id].gun_attack = map[player[id].y][player[id].x].gun_pq.top();
		map[player[id].y][player[id].x].gun_pq.pop();
	}
	return;
}

bool isVictory(int id1, int id2) {
	int act1 = player[id1].initial_attack + player[id1].gun_attack;
	int act2 = player[id2].initial_attack + player[id2].gun_attack;
	if (act1 > act2 || act1 == act2 && player[id1].initial_attack > player[id2].initial_attack) {
		player[id1].point += act1 - act2;
		return true; 
	}
	else {
		player[id2].point += act2 - act1;
		return false;
	}
}

void swapGun(int id1, int id2) {
	if (player[id2].gun_attack <= player[id1].gun_attack) {

		map[player[id2].y][player[id2].x].gun_pq.push(player[id2].gun_attack);
		player[id2].gun_attack = 0;
		return; 
	}
	int tmp = player[id2].gun_attack;
	player[id2].gun_attack = player[id1].gun_attack;
	player[id1].gun_attack = tmp;
	map[player[id2].y][player[id2].x].gun_pq.push(player[id2].gun_attack);
	player[id2].gun_attack = 0;
	return;
}

void nextMove(int id) {
	int dy = player[id].y + direct[player[id].dir][0];
	int dx = player[id].x + direct[player[id].dir][1];
	while (map[dy][dx].playerId != 0 || (dy <= 0 || dy > n || dx <= 0 || dx > n)) {
		player[id].dir = (player[id].dir + 1) % 4;
		dy = player[id].y + direct[player[id].dir][0];
		dx = player[id].x + direct[player[id].dir][1];
	}
	player[id].y = dy;
	player[id].x = dx;
	map[dy][dx].playerId = id;

	getGun(id);
	return;
}

void print(int round) {
	printf("round : %d\n", round);
	for (int y = 1; y <= n; ++y) {
		for (int x = 1; x <= n; ++x) {
			printf("%d", map[y][x].playerId);
		}
		printf("\n");
	}
	for (int t = 1; t <= m; ++t) {
		printf("%d ", player[t].point);
	}
	printf("\n");
}

void sv(int round) {
	//print(round);
	if (round == k) return;
	
	for (int t = 1; t <= m; ++t) {
		Node dest = move(t);
		if (map[dest.y][dest.x].playerId == 0) {
			//사람이 없으면 총 얻기
			getGun(t);
			map[dest.y][dest.x].playerId = t;
		}
		else {
			//사람이 있으면
			// t가 이기면
			if (isVictory(t, map[dest.y][dest.x].playerId)) {
				swapGun(t, map[dest.y][dest.x].playerId);
				nextMove(map[dest.y][dest.x].playerId);
				map[dest.y][dest.x].playerId = t;
				
				
			}
			else {
				//t가지면
				swapGun(map[dest.y][dest.x].playerId, t);
				nextMove(t);
			}
		
		}
	}
	sv(round + 1);

}
int main(void) {
	
	scanf("%d %d %d", &n, &m, &k);
	for (int y = 1; y <= n; ++y)
		for (int x = 1; x <= n; ++x)
		{
			scanf("%d", &i);
			map[y][x].playerId = 0;

			if (i != 0) map[y][x].gun_pq.push(i);
		}
	for (int t = 1; t <= m; ++t) {
		int a, b, c, d;
		scanf("%d %d %d %d", &a, &b, &c, &d);
		player[t] = { c,a,b,d,0,0 };
		map[a][b].playerId = t;
	}

	sv(0);
	for (int t = 1; t <= m; ++t) {
		printf("%d ", player[t].point);
	}
}

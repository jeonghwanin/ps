/*
���̺� �ϰ� Ǯ�� �ð����⵵ O(n*k) = O(20 * 500)
���� ���� n^2 - m (���� 399��)
������ �� ĭ���� �켱 ���� ť(�ѱ�), ���� ��� ����
��� ����Ʈ, �� �ʱ� ���·� ���� ���ݷ�
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
struct Map {
	int playerId; // 0�̸� ����
	int gun_cnt;// ���� ����, �켱���� ť ũ��s
	int gun_pq[399];// �� �켱���� ť
}map[21][21];
struct Player {
	int dir;// �÷��̾� ����
	int y;	//�÷��̾� y��ǥ
	int x;	//�÷��̾� x��ǥ
	int initial_attack;	//�ʱ� ���ݷ�
	int gun_attack;	//���� ���ݷ�
	int point; //�÷��̾� ����Ʈ
}player[31];

int n, m, k, i;
int direct[4][2] = { -1,0,0,1,1,0,0,-1 };
void sv(int round) {
	if (round == k) return;
	
	for (int t = 1; t <= m; ++t) {
		Player now = player[t];
		map[now.y][now.x].playerId = 0;
		int dy = now.y + direct[now.dir][0];
		int dx = now.x + direct[now.dir][1];
		if (dy <= 0 || dy > n || dx <= 0 || dx > n) {
			now.dir = (now.dir + 2) % 4;
			dy = now.y + direct[now.dir][0];
			dx = now.x + direct[now.dir][1];
			player[t].dir = now.dir;
		}
		if (map[dy][dx].playerId == 0) {
			if (map[dy][dx].gun_cnt == 0) {
				player[t].y = dy;
				player[t].x = dx;
				map[dy][dx].playerId = t;
				continue;
			}
			if (map[dy][dx].gun_pq[0] <= player[t].gun_attack) continue;
			player[t].gun_attack = map[dy][dx].gun_pq[0];
			map[dy][dx].gun_pq[0] = map[dy][dx].gun_pq[map[dy][dx].gun_cnt];
			//heapify

			continue;
		}
	}

}
int main(void) {
	
	scanf("%d %d %d", &n, &m, &k);
	for (int y = 1; y <= n; ++y)
		for (int x = 1; x <= n; ++x)
		{
			scanf("%d", &i);
			map[y][x].playerId = 0;
			map[y][x].gun_cnt = 0;
			if (i != 0) map[y][x].gun_pq[map[y][x].gun_cnt++] = i;
		}
	for (int t = 1; t <= m; ++t) {
		int a, b, c, d;
		scanf("%d %d %d %d", &a, &b, &c, &d);
		player[t] = { c,a,b,d,0,0 };
	}
	sv(k);
	
}

struct Node {
	int y, x;
};
Node arr[2][6][400];


int dat1[6];
int dat2[2][66];	// 0 : 수평 1 : 수직
int dat3[2][666];
int dat4[2][6666];
int dat5[2][66666];



void init(int N, int mMap[20][20])
{
	for (int t = 0; t < 6; t++)
	{
		dat1[t] = 0;
	}
	for (int t = 0; t < 66; t++)
	{
		dat2[0][t] = 0;
		dat2[1][t] = 0;
	}
	for (int t = 0; t < 666; t++)
	{
		dat3[0][t] = 0;
		dat3[1][t] = 0;
	}
	for (int t = 0; t < 6666; t++)
	{
		dat4[0][t] = 0;
		dat4[1][t] = 0;
	}
	for (int t = 0; t < 66666; t++)
	{
		dat5[0][t] = 0;
		dat5[1][t] = 0;
	}

	for(int y=0; y<N; y++)
		for (int x = 0; x < N; x++)
		{
			int l = mMap[y][x];
			int r = mMap[x][y];
			++dat1[l];

			if (y >= N - 1) continue;

			l = 10 * l + mMap[y + 1][x];
			r = 10 * r + mMap[x + 1][y];
			++dat2[0][l];
			++dat2[1][r];

			if (y >= N - 2) continue;
			l = 10 * l + mMap[y + 2][x];
			r = 10 * r + mMap[x + 2][y];
			++dat3[0][l];
			++dat3[1][r];

			if (y >= N - 3) continue;
			l = 10 * l + mMap[y + 3][x];
			r = 10 * r + mMap[x + 3][y];
			++dat4[0][l];
			++dat4[1][r];

			if (y >= N - 4) continue;
			l = 10 * l + mMap[y + 4][x];
			r = 10 * r + mMap[x + 4][y];
			++dat5[0][l];
			++dat5[1][r];

		}

}

int numberOfCandidate(int M, int mStructure[5])
{
	int ans = 0;
	int MAX = mStructure[0];
	int MIN = mStructure[0];
	for (int t = 1; t < M; t++) {
		if (MAX < mStructure[t]) { 
			MAX = mStructure[t];
		}
		if (MIN > mStructure[t]) {
			MIN = mStructure[t];
		}
	}

	int index1 = 0;
	int index2 = 0;
	for (int t = 0; t < M; t++) {
		index1 = index1 * 10 + mStructure[t];
		index2 = index2 * 10 + mStructure[M-t-1];
	}
	int ptr1 = index1;
	int ptr2 = index2;
	for (int t = MAX + 1 - MIN; t <= 5; t++) {
		if (M == 1) {
			ans += dat1[ptr1];
			ptr1 += 1;
		}
		else if (M == 2) {
			ans += dat2[0][ptr1];
			ans += dat2[1][ptr1];
			if (ptr1 != ptr2) {
				ans += dat2[0][ptr2];
				ans += dat2[1][ptr2];
			}
			ptr1 += 11;
			ptr2 += 11;
		}
		else if (M == 3) {
			ans += dat3[0][ptr1];
			ans += dat3[1][ptr1];
			if (ptr1 != ptr2) {
				ans += dat3[0][ptr2];
				ans += dat3[1][ptr2];
			}
			ptr1 += 111;
			ptr2 += 111;
		}
		else if (M == 4) {
			ans += dat4[0][ptr1];
			ans += dat4[1][ptr1];
			if (ptr1 != ptr2) {
				ans += dat4[0][ptr2];
				ans += dat4[1][ptr2];
			}
			ptr1 += 1111;
			ptr2 += 1111;
		}
		else if (M == 5) {
			ans += dat5[0][ptr1];
			ans += dat5[1][ptr1];
			if (ptr1 != ptr2) {
				ans += dat5[0][ptr2];
				ans += dat5[1][ptr2];
			}
			ptr1 += 11111;
			ptr2 += 11111;
		}
	}

	return ans;
}

int maxArea(int M, int mStructure[5], int mSeaLevel)
{


	return 0;
}
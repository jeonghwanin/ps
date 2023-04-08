#define LIST_SIZE 100000
struct Node {
    int mid;
    int mteam;
    Node* next;
    Node* prev;
};
Node list[LIST_SIZE+1];
Node head[6][6]; // mTeam, mScore
Node tail[6][6];
void init()
{
    for (int t = 1; t < 6; t++)
    { 
        for (int q = 1; q < 6; q++)
        {
            head[t][q].next = &tail[t][q];
            tail[t][q].prev = &head[t][q];

        }
    }
}

void hire(int mID, int mTeam, int mScore)
{
    list[mID] = { mID,mTeam, (Node*)0, (Node*)0,};

    list[mID].next = head[mTeam][mScore].next;
    head[mTeam][mScore].next = &list[mID];

    list[mID].prev = &head[mTeam][mScore];
    list[mID].next->prev = &list[mID];

}

void fire(int mID)
{
    list[mID].prev->next = list[mID].next;
    list[mID].next->prev = list[mID].prev;
}

void updateSoldier(int mID, int mScore)
{
    int mTeam = list[mID].mteam;
    fire(mID);
    hire(mID, mTeam, mScore);
}

void updateTeam(int mTeam, int mChangeScore)
{
    if (mChangeScore == 0) return;
    else if (mChangeScore < 0)
    {
        for (int t = 2; t <= 5; t++)
        {
            int k = t + mChangeScore;
            if (k <= 1) k = 1;

            head[mTeam][t].next->prev = tail[mTeam][k].prev;
            tail[mTeam][k].prev->next = head[mTeam][t].next;
            tail[mTeam][t].prev->next = &tail[mTeam][k];
            tail[mTeam][k].prev = tail[mTeam][t].prev;
            head[mTeam][t].next = &tail[mTeam][t];
            tail[mTeam][t].prev = &head[mTeam][t];
        }
    }
    else if (mChangeScore > 0)
    {
        for (int t = 4; t >= 1; t--)
        {
            int k = t + mChangeScore;
            if (k >= 5) k = 5;
            head[mTeam][t].next->prev = tail[mTeam][k].prev;
            tail[mTeam][k].prev->next = head[mTeam][t].next;
            tail[mTeam][t].prev->next = &tail[mTeam][k];
            tail[mTeam][k].prev = tail[mTeam][t].prev;
            head[mTeam][t].next = &tail[mTeam][t];
            tail[mTeam][t].prev = &head[mTeam][t];
        }
    }
}

int bestSoldier(int mTeam)
{
    int MAXID = -21e8; 
    bool find = false;
    for (int t = 5; t >= 1; t--)
    {
        Node* ptr = head[mTeam][t].next;
        while (ptr != &tail[mTeam][t]) {
            if (MAXID < ptr->mid) { 
                MAXID = ptr->mid;
                find = true;
            }
            ptr = ptr->next;
        }
        if (find) break;
    }
    return MAXID;
}
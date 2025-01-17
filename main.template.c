#include "api.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define SWAP(a, b, type) \
    {                    \
        type tmp = a;    \
        a = b;           \
        b = tmp;         \
    }
int n_mails, n_queries;
mail *mails;
query *queries;
int cmp(const void *a, const void *b) {
    if (queries[*(int *)a].data.find_similar_data.threshold <
        queries[*(int *)b].data.find_similar_data.threshold)
        return -1;
    else
        return 1;
}
#define NUM_MAILS 10000
#define NUM_NAMES 1024

int dsu_lead[NUM_NAMES];
int dsu_size[NUM_NAMES];
int dsu_maxsize;
int dsu_numg;
int dsu_one;
int dsu_find(int x) {
    if (dsu_lead[x] == x) return x;
    return dsu_lead[x] = dsu_find(dsu_lead[x]);
}
void dsu_U(int x, int y) {
    x = dsu_find(x);
    y = dsu_find(y);
    if (x == y) return;
    if (dsu_size[x] == 1) dsu_one--;
    if (dsu_size[y] == 1) dsu_one--;
    if (dsu_size[x] < dsu_size[y]) {
        SWAP(x, y, int)
    }
    int ts = dsu_size[x] + dsu_size[y];
    dsu_lead[y] = x;
    dsu_size[x] = ts;
    dsu_numg--;
    if (ts > dsu_maxsize) dsu_maxsize = ts;
}
const char *sim_s = "SIM_S_INIT";
double similar[NUM_MAILS][NUM_MAILS];
int num_tokens[NUM_MAILS] = NUM_TOKENS_INIT;
int send_ids[NUM_MAILS] = SEND_IDS_INIT;
int recv_ids[NUM_MAILS] = RECV_IDS_INIT;
void build_similar(int n) {
    const char *pos = sim_s;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            double AND = (((*pos) - '0') << 6) | ((*(pos + 1)) - '0');
            similar[j][i] = similar[i][j] =
                AND / (num_tokens[i] + num_tokens[j] - AND);
            pos += 2;
        }
    }
}
int candidates_1[NUM_MAILS], candidates_2[NUM_MAILS];
int ans_group[2];
int find_similar_queries[NUM_MAILS][1024];
int num_find_similar_queries[NUM_MAILS];

void G_A(int qid) {
    int len = queries[qid].data.group_analyse_data.len;
    int *mids = queries[qid].data.group_analyse_data.mids;
    dsu_numg = 0;
    dsu_maxsize = 1;

    for (int i = 0; i < len; i++) {
        dsu_lead[send_ids[mids[i]]] = -1;
        dsu_lead[recv_ids[mids[i]]] = -1;
        dsu_size[send_ids[mids[i]]] = 1;
        dsu_size[recv_ids[mids[i]]] = 1;
    }
    for (int i = 0; i < len; i++) {
        if (dsu_lead[send_ids[mids[i]]] == -1) {
            dsu_numg++;
            dsu_lead[send_ids[mids[i]]] = send_ids[mids[i]];
        }
        if (dsu_lead[recv_ids[mids[i]]] == -1) {
            dsu_numg++;
            dsu_lead[recv_ids[mids[i]]] = recv_ids[mids[i]];
        }
    }
    dsu_one = dsu_numg;

    for (int i = 0; i < len; i++) dsu_U(send_ids[mids[i]], recv_ids[mids[i]]);
    ans_group[0] = dsu_numg - dsu_one;
    ans_group[1] = dsu_maxsize;
    api.answer(qid, ans_group, 2);
}
int answer_find_similar(int qid, int candidates[], int num_candidates,
                        int answer[]) {
    int answer_len = 0, mid = queries[qid].data.find_similar_data.mid;
    double threshold = queries[qid].data.find_similar_data.threshold;
    for (int i = 0; i < num_candidates; i++) {
        if (similar[mid][candidates[i]] > threshold && candidates[i] != mid) {
            answer[answer_len++] = candidates[i];
        }
    }
    if (answer_len)
        api.answer(qid, answer, answer_len);
    else
        api.answer(qid, NULL, 0);
    return answer_len;
}
int main() {
    api_init(&n_mails, &n_queries, &mails, &queries);
    build_similar(NUM_MAILS);
    for (int i = 0; i < n_queries; i++) {
        if (queries[i].type == find_similar) {
            int mid = queries[i].data.find_similar_data.mid;
            find_similar_queries[mid][num_find_similar_queries[mid]++] = i;
        }
    }
    for (int i = 0; i < NUM_MAILS; i++) {
        qsort(find_similar_queries[i], num_find_similar_queries[i], sizeof(int),
              cmp);
    }
    for (int i = 0; i < NUM_MAILS; i++) {
        int *current = candidates_1, *previous = candidates_2;
        int num_previous = NUM_MAILS;
        for (int i = 0; i < NUM_MAILS; i++) previous[i] = i;
        for (int j = 0; j < num_find_similar_queries[i]; j++) {
            num_previous = answer_find_similar(find_similar_queries[i][j],
                                               previous, num_previous, current);
            SWAP(previous, current, int *);
        }
    }
    for (int i = 0; i < n_queries; i++) {
        if (queries[i].type == group_analyse &&
            queries[i].data.group_analyse_data.len <= 150) {
            G_A(i);
        }
    }
    return 0;
}

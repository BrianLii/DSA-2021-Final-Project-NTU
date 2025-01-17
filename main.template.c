#include "api.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define NUM_MAILS 10000
#define NUM_NAMES 1024
query *queries;

/* Helper Functions */
int cmp(const void *a, const void *b) {
    if (queries[*(int *)a].data.find_similar_data.threshold <
        queries[*(int *)b].data.find_similar_data.threshold)
        return -1;
    else
        return 1;
}
#define SWAP(a, b, type) \
    {                    \
        type tmp = a;    \
        a = b;           \
        b = tmp;         \
    }

/* Disjoint Set Union */
int dsu_lead[NUM_NAMES];
int dsu_size[NUM_NAMES];
int dsu_maxsize, dsu_num_groups, dsu_num_ones;
int dsu_find(int x) {
    if (dsu_lead[x] == x) return x;
    return dsu_lead[x] = dsu_find(dsu_lead[x]);
}
void dsu_union(int x, int y) {
    x = dsu_find(x);
    y = dsu_find(y);
    if (x == y) return;
    if (dsu_size[x] == 1) dsu_num_ones--;
    if (dsu_size[y] == 1) dsu_num_ones--;
    if (dsu_size[x] < dsu_size[y]) {
        SWAP(x, y, int)
    }
    dsu_size[x] += dsu_size[y];
    dsu_lead[y] = x;
    dsu_num_groups--;
    if (dsu_size[x] > dsu_maxsize) dsu_maxsize = dsu_size[x];
}

/* Find Similarity */
const char *encoded_intersections = "ENCODED_INTERSECTIONS";
double similar[NUM_MAILS][NUM_MAILS];
int num_tokens[NUM_MAILS] = NUM_TOKENS_INIT;
int candidates_1[NUM_MAILS], candidates_2[NUM_MAILS];
int find_similar_queries[NUM_MAILS][1024];
int num_find_similar_queries[NUM_MAILS];
void build_similar(int n) {
    const char *current = encoded_intersections;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            double intersection =
                (((*current) - '0') << 6) | ((*(current + 1)) - '0');
            similar[j][i] = similar[i][j] =
                intersection / (num_tokens[i] + num_tokens[j] - intersection);
            current += 2;
        }
    }
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

/* Group Analyse */
int send_ids[NUM_MAILS] = SEND_IDS_INIT;
int recv_ids[NUM_MAILS] = RECV_IDS_INIT;
void answer_group_analyse(int qid) {
    static int answer_group[2];
    int length_mids = queries[qid].data.group_analyse_data.len;
    int *mids = queries[qid].data.group_analyse_data.mids;
    dsu_num_groups = 0;
    dsu_maxsize = 1;

    for (int i = 0; i < length_mids; i++) {
        dsu_lead[send_ids[mids[i]]] = -1;
        dsu_lead[recv_ids[mids[i]]] = -1;
    }
    for (int i = 0; i < length_mids; i++) {
        if (dsu_lead[send_ids[mids[i]]] == -1) {
            dsu_num_groups++;
            dsu_lead[send_ids[mids[i]]] = send_ids[mids[i]];
            dsu_size[send_ids[mids[i]]] = 1;
        }
        if (dsu_lead[recv_ids[mids[i]]] == -1) {
            dsu_num_groups++;
            dsu_lead[recv_ids[mids[i]]] = recv_ids[mids[i]];
            dsu_size[recv_ids[mids[i]]] = 1;
        }
    }
    dsu_num_ones = dsu_num_groups;

    for (int i = 0; i < length_mids; i++) {
        dsu_union(send_ids[mids[i]], recv_ids[mids[i]]);
    }
    answer_group[0] = dsu_num_groups - dsu_num_ones;
    answer_group[1] = dsu_maxsize;
    api.answer(qid, answer_group, 2);
}
int main() {
    int n_mails, n_queries;
    mail *mails;
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
            answer_group_analyse(i);
        }
    }
    return 0;
}

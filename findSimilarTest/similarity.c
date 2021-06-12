#include "api.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
int n_mails,n_queries;
mail *mails;
query *queries;
int answer[20000];
void FindSimilar(int qid, double similarity[1000][10000]){
	int ans_len = 0, mid = queries[qid].data.find_similar_data.mid;
	double threshold = queries[qid].data.find_similar_data.threshold;
	if(mid>1000) return;
	for(int i=0;i<n_mails;i++){
		if(mails[i].id!=mid&&similarity[mid][mails[i].id]>=threshold) answer[ans_len++]=mails[i].id;
	}
	if(ans_len!=0) api.answer(qid,answer,ans_len);
	else api.answer(qid,NULL,0);
}
int main(){
	api_init(&n_mails, &n_queries, &mails, &queries);
	static double similarity[][] = 
	for(int i=0;i<n_queries;i++)
	{
		if(queries[i].type==find_similar) FindSimilar(i,similarity);
	}
}
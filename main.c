#include "api.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#define SWAP(a,b,type) {type tmp=a;a=b;b=tmp;}
int n_mails,n_queries;
mail *mails;
query *queries;
int cmp (const void * a, const void * b)
{
	if(queries[*(int*)a].data.find_similar_data.threshold<
	   queries[*(int*)b].data.find_similar_data.threshold)
		return -1;
	else return 1;
}
inline int chrtoi(char c);
int dsu_lead[20020];
int dsu_size[20020];
int dsu_maxsize;
int dsu_numg;
int dsu_one;
int dsu_find(int x)
{
	if(dsu_lead[x]==x)return x;
	return dsu_lead[x]=dsu_find(dsu_lead[x]);
}
void dsu_U(int x,int y)
{
	x=dsu_find(x);y=dsu_find(y);
	if(x==y)return;
	if(dsu_size[x]==1)dsu_one--;
	if(dsu_size[y]==1)dsu_one--;
	if(dsu_size[x]<dsu_size[y])
	{
		SWAP(x,y,int)
	}
	int ts=dsu_size[x]+dsu_size[y];
	dsu_lead[y]=x;
	dsu_size[x]=ts;
	dsu_numg--;
	if(ts>dsu_maxsize)
		dsu_maxsize=ts;
}
INIT_sim_s
double similar[10000][10000];
int token_set_size[10000]=TOKEN_SET_SIZE_INIT;
int from_hash[20020]=FROM_HASH_INIT;
int to_hash[20020]=TO_HASH_INIT;
void build_similar(int n)
{
	const char *pos=sim_s;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<=i;j++)
		{
			double AND=(((*pos)-'0')<<6)|((*(pos+1))-'0');
			similar[j][i]=similar[i][j]=AND/(token_set_size[i]+token_set_size[j]-AND);
			pos+=2;
		}
	}
}
int ans_start[10000];
int ans_1[10000];
int ans_2[10000];
int mail_queue[10000][1000];
int ans_group[2];
int mail_queue_size[10000];
void G_A(int qid)
{
	int len=queries[qid].data.group_analyse_data.len;
	int *mid=queries[qid].data.group_analyse_data.mids;
	dsu_numg=0;
	dsu_maxsize=1;
	//make set
	for(int i=0;i<len;i++)
	{
		dsu_lead[from_hash[mid[i]]]=-1;
		dsu_lead[to_hash[mid[i]]]=-1;
		dsu_size[from_hash[mid[i]]]=1;
		dsu_size[to_hash[mid[i]]]=1;
	}
	for(int i=0;i<len;i++)
	{
		if(dsu_lead[from_hash[mid[i]]]==-1)
		{
			dsu_numg++;
			dsu_lead[from_hash[mid[i]]]=from_hash[mid[i]];
		}
		if(dsu_lead[to_hash[mid[i]]]==-1)
		{
			dsu_numg++;
			dsu_lead[to_hash[mid[i]]]=to_hash[mid[i]];
		}
	}
	dsu_one=dsu_numg;

	for(int i=0;i<len;i++)
		dsu_U(from_hash[mid[i]],to_hash[mid[i]]);
	ans_group[0]=dsu_numg-dsu_one;
	ans_group[1]=dsu_maxsize;
	api.answer(qid,ans_group,2);
}
int FindSimilar(int qid,int last[],int last_size,int answer[])
{
	int ans_len=0, mid=queries[qid].data.find_similar_data.mid;
	double threshold=queries[qid].data.find_similar_data.threshold;
	for(int i=0;i<last_size;i++)
	{
		if(similar[mid][last[i]]>threshold&&last[i]!=mid)
		{
			answer[ans_len++]=last[i];
		}
	}
	if(ans_len!=0)api.answer(qid,answer,ans_len);
	else api.answer(qid,NULL,0);
	return ans_len;
}
int main()
{
	api_init(&n_mails, &n_queries, &mails, &queries);
	build_similar(10000);
	for(int i=0;i<10000;i++)ans_start[i]=i;
	for(int i=0;i<n_queries;i++)
	{
		if(queries[i].type==find_similar)
		{
			int mid=queries[i].data.find_similar_data.mid;
			mail_queue[mid][mail_queue_size[mid]++]=i;
		}
	}
	for(int i=0;i<10000;i++)
	{
		int *arr=mail_queue[i];
		int n=mail_queue_size[i];
		qsort(arr,n,sizeof(int),cmp);
	}
	for(int i=0;i<10000;i++)
	{
		int *last,*now,last_len;
		if(mail_queue_size[i])
			last_len=FindSimilar(mail_queue[i][0],ans_start,10000,ans_1);
		last=ans_1;
		now=ans_2;
		for(int j=1;j<mail_queue_size[i];j++)
		{
			last_len=FindSimilar(mail_queue[i][j],last,last_len,now);
			SWAP(last,now,int *)
			if(now==ans_start)now=ans_2;
		}
	}
	for(int i=0;i<n_queries;i++)
	{
		if(queries[i].type==group_analyse&&queries[i].data.group_analyse_data.len<=150)
		{
			G_A(i);
		}
	}
	return 0;
}

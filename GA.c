#include "api.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#define SWAP(a,b,type) {type tmp=a;a=b;b=tmp;}
#define TOK 1
#define OPR 2
#define isop(c) (c=='('||c==')'||c=='&'||c=='!'||c=='|')
#define isch(c) (('0'<=c&&c<='9')||('a'<=c&&c<='z'))
int n_mails,n_queries;
mail *mails;
query *queries;
typedef struct node
{
	int type,data;
}node;
typedef long long ll;
int ll_compare (const void *a, const void *b)
{
	if(*(ll*)a<*(ll*)b)return -1;
	if(*(ll*)a==*(ll*)b)return 0;
	return 1;
}
inline int lower_bound(ll *a,int n,ll k);
int lower_bound(ll *a,int n,ll k)
{
	int l=0,r=n-1;
	int res=n;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(a[mid]<k)
		{
			l=mid+1;
		}
		else
		{
			res=mid;
			r=mid-1;
		}
	}
	return res;
}
ll buff[3000];
int unique(ll *a,int n)
{
	int tail=0;
	for(int i=0;i<n;i++)
	{
		buff[tail++]=a[i];
		int r=i;
		for(int j=i;j<n;j++)
		{
			if(a[j]==a[i])r=j;
			else break;
		}
		i=r;
	}
	for(int i=0;i<tail;i++)
		a[i]=buff[i];
	return tail;
}
const ll base1=15401689;
const ll base2=10580467;
const ll mod=9196699;
ll hash_string(const char *s,int len)
{
	ll h1=0;
	for(int i=0;i<len;i++)h1=(h1*base1+s[i])%mod;
	ll h2=0;
	for(int i=0;i<len;i++)h2=(h2*base2+s[i])%mod;
	return h1*mod+h2;
}
ll *token_set[10020];
int token_set_size[10020];
void build_token_set(int email_id)
{
	char *content=mails[email_id].content;
	int email_len=strlen(content);
	int token_cnt=0;
	for(int i=0;i<email_len;i++)
	{
		if(!isch(content[i]))continue;
		int r=i;
		for(int j=i;j<email_len;j++)
		{
			if(isch(content[j]))r=j;
			else break;
		}
		token_cnt++;
		i=r;
	}
	token_set[email_id]=calloc(token_cnt,sizeof(ll));
	token_set_size[email_id]=token_cnt;
	token_cnt=0;
	for(int i=0;i<email_len;i++)
	{
		if(!isch(content[i]))continue;
		int r=i;
		for(int j=i;j<email_len;j++)
		{
			if(isch(content[j]))r=j;
			else break;
		}
		token_set[email_id][token_cnt++]=hash_string(content+i,r-i+1);
		i=r;
	}
	qsort(token_set[email_id],token_cnt,sizeof(ll),ll_compare);
}
int token_in_email(const char *token,int token_len,int email_id)
{
	ll h=hash_string(token,token_len);
	if(bsearch(&h,token_set[email_id], token_set_size[email_id], sizeof(ll), ll_compare)!=NULL)return 1;
	else return 0;
}
node in[3000];
node post[3000];
node stack[3000];
bool eval(const char *exp,int email_id)
{
	int explen=strlen(exp);
	int inorder_size=0;
	//build inorder
	for(int i=0;i<explen;i++)
	{
		if(isop(exp[i]))
		{
			in[inorder_size].type=OPR;
			in[inorder_size].data=exp[i];
			inorder_size++;
		}
		else
		{
			int token_end=i;
			for(int j=i;j<explen;j++)
			{
				if(!isop(exp[j]))token_end=j;
				else break;
			}
			in[inorder_size].type=TOK;
			in[inorder_size].data=token_in_email(exp+i,token_end-i+1,email_id);
			inorder_size++;
			i=token_end;
		}
	}
	int stack_size=0;
	int postorder_size=0;
	for(int i=0;i<inorder_size;i++)
	{
		if(in[i].type==TOK)
		{
			post[postorder_size++]=in[i];
		}
		else if(in[i].data=='(')
		{
			stack[stack_size++]=in[i];
		}
		else if(in[i].data==')')
		{
			while(stack[stack_size-1].data!='(')
			{
				post[postorder_size++]=stack[stack_size-1];
				stack_size--;
			}
			stack_size--;
		}
		else if(in[i].data=='!')
		{
			while(stack_size>0&&stack[stack_size-1].data!='('&&stack[stack_size-1].data!='&'&&stack[stack_size-1].data!='|')
			{
				post[postorder_size++]=stack[stack_size-1];
				stack_size--;
			}
			stack[stack_size++]=in[i];
		}
		else if(in[i].data=='&')
		{
			while(stack_size>0&&stack[stack_size-1].data!='('&&stack[stack_size-1].data!='|')
			{
				post[postorder_size++]=stack[stack_size-1];
				stack_size--;
			}
			stack[stack_size++]=in[i];
		}
		else if(in[i].data=='|')
		{
			while(stack_size>0&&stack[stack_size-1].data!='(')
			{
				post[postorder_size++]=stack[stack_size-1];
				stack_size--;
			}
			stack[stack_size++]=in[i];
		}
	}
	while(stack_size>0)
	{
		post[postorder_size++]=stack[stack_size-1];
		stack_size--;
	}
	stack_size=0;
	for(int i=0;i<postorder_size;i++)
	{
		if(post[i].type==OPR)
		{
			if(post[i].data=='!')
			{
				stack[stack_size-1].data^=1;
			}
			else if(post[i].data=='|')
			{
				stack[stack_size-2].data|=stack[stack_size-1].data;
				stack_size--;
			}
			else if(post[i].data=='&')
			{
				stack[stack_size-2].data&=stack[stack_size-1].data;
				stack_size--;
			}
		}
		else
		{
			stack[stack_size++]=post[i];
		}
	}
	return stack[0].data;
}

int dsu_lead[3000];
int dsu_size[3000];
int dsu_maxsize;
int dsu_numg;
void dsu_init(int n)
{
	for(int i=0;i<n;i++)
	{
		dsu_lead[i]=i;
		dsu_size[i]=1;
	}
	dsu_maxsize=1;
	dsu_numg=n;
}
int dsu_find(int x)
{
	if(dsu_lead[x]==x)return x;
	return dsu_lead[x]=dsu_find(dsu_lead[x]);
}
void dsu_U(int x,int y)
{
	x=dsu_find(x);y=dsu_find(y);
	if(x==y)return;
	int ts=dsu_size[x]+dsu_size[y];
	dsu_lead[y]=x;
	dsu_size[x]=ts;
	dsu_numg--;
	if(ts>dsu_maxsize)
		dsu_maxsize=ts;
}
int answer[20000];
ll name_hash[3000];

void G_A(int query_id)
{
	int len=queries[query_id].data.group_analyse_data.len;
	int *mid=queries[query_id].data.group_analyse_data.mids;
	for(int i=0;i<len;i++)
	{
		name_hash[i*2]=hash_string(mails[mid[i]].from,strlen(mails[mid[i]].from));
		name_hash[i*2+1]=hash_string(mails[mid[i]].to,strlen(mails[mid[i]].to));
	}
	qsort(name_hash,len*2,sizeof(ll),ll_compare);
	int n=unique(name_hash,len*2);
	dsu_init(n);
	for(int i=0;i<len;i++)
	{
		ll h1=hash_string(mails[mid[i]].from,strlen(mails[mid[i]].from));
		ll h2=hash_string(mails[mid[i]].to,strlen(mails[mid[i]].to));
		h1=lower_bound(name_hash,n,h1);
		h2=lower_bound(name_hash,n,h2);
		dsu_U(h1,h2);
	}
	answer[0]=dsu_numg;
	answer[1]=dsu_maxsize;
	api.answer(query_id,answer,2);
}

int main(void)
{
	api_init(&n_mails, &n_queries, &mails, &queries);
	for(int i=0;i<n_queries;i++)
	{
		if(queries[i].type==group_analyse)
		{
			G_A(i);
		}
	}
	return;
	for(int i=0;i<n_mails;i++)
	{
		for(int j=0;;j++)
		{
			if(mails[i].content[j]==0)break;
			else mails[i].content[j]=tolower(mails[i].content[j]);
		}
		build_token_set(i);
	}
	for(int i=0;i<n_queries;i++)
	{
		if(queries[i].type==expression_match)
		{
			int ans_len=0;
			for(int j=0;j<n_mails;j++)
                if(eval(queries[i].data.expression_match_data.expression,j))
                    answer[ans_len++]=j;
			if(ans_len!=0)api.answer(i,answer,ans_len);
			else api.answer(i,NULL,0);
		}
	}
	return 0;
}


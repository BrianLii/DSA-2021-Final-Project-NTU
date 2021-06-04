#include "api.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>
#define SWAP(a,b,type) {type tmp=a;a=b;b=tmp;}
#define TOK 1
#define OPR 2
#define ll long long
int n_mails,n_queries;
mail *mails;
query *queries;
int answer[20000];
//change content to lowercase, split token and create hash table
struct hash_pair{
	ll hash1,hash2;
};
struct hash_pair* *mails_hash;
ll *mails_tokennum,seed=13131,base=15401689,mod1=73907987,mod2=16523471;
//hash_pair compare functions
bool isgreater(const struct hash_pair a, const struct hash_pair b){
	if(a.hash1==b.hash1) return a.hash2 > b.hash2;
	return a.hash1 > b.hash1;
}
bool isequal(const struct hash_pair a,const struct hash_pair b){
	if(a.hash1==b.hash1&&a.hash2==b.hash2) return 1;
	return 0;
}
int hp_cmp(const void *a, const void *b){
	struct hash_pair c = *(struct hash_pair*) a, d = *(struct hash_pair*) b;
	if(isequal(c,d)) return 0;
	if(isgreater(c,d)) return 1;
	else return -1;
}
void content2hash(char *content,int len,int z){
	int token_counter = 0, capacity = 1;
	struct hash_pair *h = calloc(1,sizeof(struct hash_pair)),temp;
	temp.hash1 = 0;
	temp.hash1 = 0;
	for(int i=0,j=0;content[i]!='\0';i=j+1){
		while(!isalnum((int) content[i])) i++;
		j=i;
		while(isalnum((int) content[j])){
			content[j] = (char) tolower((int) content[j]);
			temp.hash1 = (temp.hash1*seed + (int) content[j]) % mod1;
			temp.hash2 = (temp.hash2 + (int) content[j]*base) % mod2;
			j++;
		}
		j--;
		//i to j is a token
		if(token_counter==capacity){
			capacity = capacity<<1;
			h = realloc(h, capacity*sizeof(struct hash_pair));
		}
		h[token_counter] = temp;
		token_counter++;
		temp.hash1 = 0;
		temp.hash2 = 0;
	}
	h = realloc(h, token_counter*sizeof(struct hash_pair));//save some memory
	qsort(h,token_counter,sizeof(struct hash_pair),hp_cmp);//sort hash table
	mails_hash[z] = h;
	mails_tokennum[z] = token_counter;
}
//expression
typedef struct node
{
	int type,data;
}node;
int token_in_email(const char *token,int token_len,char *email,int email_len)
{
	for(int i=0;i<email_len-token_len;i++)
	{
		if(strncmp(token,email+i,token_len)==0)return 1;
	}
	return 0;
}
bool isop(char c)
{
	return (c=='('||c==')'||c=='&'||c=='!'||c=='&'||c=='|');
}
node in[3000];
node post[3000];
node stack[3000];
bool eval(const char *exp,const char *e_mail,int e_mail_len)
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
			in[inorder_size].data=token_in_email(exp+i,token_end-i+1,e_mail,e_mail_len);
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
		else
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
//main
int main(void)
{
	api_init(&n_mails, &n_queries, &mails, &queries);
	//change content to lowercase, split token and create hash table
	mails_hash = malloc(n_mails * sizeof(struct hash_pair));
	mails_tokennum = malloc(n_mails * sizeof(ll));
	for(int i=0;i<n_mails;i++){
		content2hash(mails[i].content,strlen(mails[i].content),i);
	}
	for(int i=0;i<n_mails;i++)
	{
		for(int j=0;;j++)
		{
			if(mails[i].content[j]==0)break;
			else mails[i].content[j]=tolower(mails[i].content[j]);
		}
	}
	for(int i=0;i<n_queries;i++)
	{
		if(queries[i].type == expression_match)
		{
			int cnt=0;
			for(int j=0;j<n_mails;j++)
			{
				int len=strlen(mails[j].content);
                if(eval(queries[i].data.expression_match_data.expression,mails[j].content,len))
                {
                    answer[cnt]=j;
                    cnt++;
                }
			}
			api.answer(i,answer,cnt);
		}
	}
	return 0;
}


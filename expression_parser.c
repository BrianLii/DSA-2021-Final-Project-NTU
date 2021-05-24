#include "api.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#define SWAP(a,b,type) {type tmp=a;a=b;b=tmp;}
#define TOK 1
#define OPR 2
typedef struct node
{
	int type,data;
}node;
int eval_token(const char *token,int len,const char *e_mail,int e_mail_len)
{
	for(int i=0;i<e_mail_len-len;i++)
	{
		for(int j=0;j<len;j++)
		{
			if(e_mail[i+j]!=token[i])
				break;
			if(j==len-1) return 1;
		}
	}
	return 0;
}
bool isop(char c)
{
	return(c=='('||c==')'||c=='&'||c=='!'||c=='&'||c=='|');
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
			in[inorder_size].data=eval_token(exp+i,token_end-i+1,e_mail,e_mail_len);
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
signed main()
{
	int *n_mails,*n_queries;
	mail **mails;
	query **queries;
	printf("INIT\n");
	api_init(n_mails, n_queries, mails,queries);
	printf("INIT_finish");
	for(int i=0;i<*n_queries;i++)
	{
		if(queries[i]->type == expression_match)
		{
			int answer[*n_mails+1],cnt=0;
			for(int j=0;j<*n_mails;j++)
			{
				int len=strlen(mails[j]->content);

                if(eval(queries[i]->data.expression_match_data.expression,mails[j]->content,len))
                {
                    answer[cnt]=j;
                    cnt++;
                }
			}
			api.answer(i,answer,cnt);
		}
	}
	//printf("%d",eval(s));
	return 0;
}


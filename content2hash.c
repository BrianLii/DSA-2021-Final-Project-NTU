#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>
#define SWAP(a,b,type) {type tmp=a;a=b;b=tmp;}
#define TOK 1
#define OPR 2
#define ll long long
struct hash_pair{
	ll hash1,hash2;
};
struct hash_pair *mails_hash;
ll mails_tokennum;
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
ll seed=13131,base=15401689,mod1=73907987,mod2=16523471;
void content2hash(char *content){
	ll len = strlen(content), token_counter = 0, capacity = 1;
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
		printf("%lld %lld\n",temp.hash1,temp.hash2);
		h[token_counter] = temp;
		token_counter++;
		temp.hash1 = 0;
		temp.hash2 = 0;
	}
	h = realloc(h, token_counter*sizeof(struct hash_pair));
	qsort(h,token_counter,sizeof(struct hash_pair),hp_cmp);
	mails_hash = h;
	mails_tokennum = token_counter;
}
int main(void)
{
	char s[100000];
	unsigned int n;
	scanf("%u",&n);
	for(int i=0;i<n;i++){
		scanf("%c",&s[i]);
	}
	s[n]='\0';
	content2hash(s);
	for(int i=0;i<n;i++){
		printf("%c",s[i]);
	}
	printf("\n");
	for(int i=0;i<mails_tokennum;i++){
		printf("%lld %lld\n",mails_hash[i].hash1,mails_hash[i].hash2);
	}
	return 0;
}


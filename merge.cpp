#include<fstream>
#include<iostream>
using namespace std;
int chrtoi(char c)
{
	if('a'<=c&&c<='z')return c-'a';
	if('A'<=c&&c<='Z')return 26+c-'A';
	else return 52+c-'0';
}
int Htoi(char c1,char c2)
{
	return 62*chrtoi(c1)+chrtoi(c2);
}
int main()
{
    ofstream fout;
    string filename="main.c";
    fout.open("main_merge.c");
    ifstream f,a;
    string buf;
    f.open(filename);
    a.open("./sim_AND.txt");
    while(getline(f,buf)){
		if(buf=="INIT_sim_s"){
            fout<<"const char *sim_s=\"";
			string tmp;
			a>>tmp;
			string nbuf="";
			int n=10000;
			for(int i=0;i<n;i++)
			{
				for(int j=0;j<=i;j++)
				{
					int num=Htoi(tmp[(i*10000+j)*2],tmp[(i*10000+j)*2+1]);
					nbuf+=num/64+'0';
					if(num/64+'0'=='\\')nbuf+='\\';
					nbuf+=num%64+'0';
					if(num%64+'0'=='\\')nbuf+='\\';
					//nbuf+=tmp[(i*10000+j)*2];
					//nbuf+=tmp[(i*10000+j)*2+1];
				}
			}
            fout<<nbuf;
            fout<<"\";\n";
        }
        else
            fout<<buf<<endl;
    }
    f.close();
    a.close();
}

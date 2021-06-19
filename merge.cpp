#include<fstream>
#include<iostream>
using namespace std;
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
					nbuf+=tmp[(i*10000+j)*2];
					nbuf+=tmp[(i*10000+j)*2+1];
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

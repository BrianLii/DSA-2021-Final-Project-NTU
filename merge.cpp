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
            int N=5000,M=10000;
            for(int i=0;i<N*M*2;i++)nbuf+=tmp[i];
            fout<<nbuf;
            fout<<"\";\n";
        }
        else
            fout<<buf<<endl;
    }
    f.close();
    a.close();
}

#include<fstream>
#include<iostream>
using namespace std;
int main()
{
    ofstream fout;
    fout.open("test.c");
    ifstream f;
    string buf;
    f.open("start.txt");
    while(getline(f,buf)){
        fout<<buf<<endl;
    }
    f.close();
    fout<<"const char *sim_s=\"";
    f.open("../sim_AND.txt");
	f>>buf;
	//control the size of the table
	//20000*10000 == table[10000][10000]
	string nbuf="";
	for(int i=0;i<20000*10000;i++)nbuf+=buf[i];
	fout<<nbuf;
    f.close();
    fout<<"\";"<<endl;
    f.open("end.txt");
    while(getline(f,buf)){
        fout<<buf<<endl;
    }
    f.close();
}


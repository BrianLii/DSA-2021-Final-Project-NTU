#include<fstream>
#include<iostream>
using namespace std;
int main()
{
    ofstream fout;
    string filename;
    cin>>filename;
    fout.open("main.c");
    ifstream f,a;
    string buf;
    f.open(filename);
    a.open("../sim_AND.txt");
    while(getline(f,buf)){
        if(buf=="static char *sim_s=\"abc\";"){
            fout<<"const char *sim_s=\"";
            a>>buf;
            string nbuf="";
            //control the size of the table
            //20000*10000 == table[10000][10000]
            for(int i=0;i<20000*10000;i++)nbuf+=buf[i];
            fout<<nbuf;
            fout<<"\";"<<endl;
        }
        else
            fout<<buf<<endl;
    }
    f.close();
    a.close();
}


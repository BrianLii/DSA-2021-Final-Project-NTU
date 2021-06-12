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
    fout<<"    static double similarity[1000][10000]={";
    f.open("similarity.txt");
    for(int i=1;i<=1000;i++)
    {
        if(i!=1) fout<<",";
        fout<<"{";
        for(int j=1;j<=10000;j++)
        {
            if(j!=1) fout<<",";
            f>>buf;
            fout<<buf;
        }
        fout<<"}";
    }
    f.close();
    fout<<"};"<<endl;
    f.open("end.txt");
    while(getline(f,buf)){
        fout<<buf<<endl;
    }
    f.close();
}


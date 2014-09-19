#include "env.hpp"
#include "malloc.hpp"
#include <time.h>
#include <fstream>
#include  <stdio.h>
#include  <unistd.h>
extern env env_inst;
void run_enron();

#define FILE_ALERT ifstream fin(optarg); \
		   if(!fin.is_open()){cout<<"File "<<optarg<<" Not Exist!"<<endl;exit(1);} \
		   fin.close();

#define PARA_ALERT if(atoi(optarg)<=0){cout<<"Invalid Parameter "<<optarg<<" !"<<endl;exit(1);}
#define CMD_ALERT cout<<"Error In Command!"<<endl;exit(1); 
int main(int argc, char** argv) {
    int ch;
    opterr = 0;
    while((ch = getopt(argc,argv,"I:O:h"))!= -1)
    {
		switch(ch)
		{
			case 'I': {FILE_ALERT env_inst.INPUT_DOC=optarg;break;}
			case 'O': env_inst.OUTPUT_DEGREE=optarg;break;
			case 'h': 
			cout<<"Social Influence Analysis Toolkit."<<endl;
			cout<<"Version 1.0"<<endl;
		
			cout<<"-I: The input document file of enron with the default value ./input/mailgraph.txt."<<endl;
			cout<<"-O: The output file of enron which shows the user degree. The default value is ./output/degree.txt."<<endl;
			cout<<"-h: Print help."<<endl;
			exit(1);			   
			default: CMD_ALERT
		}
    }
    clock_t start,finish;
    start=clock();
    cout<<env_inst<<endl;
    
    //Begin Running
    run_enron();
    //End Running
     
    finish=clock();
    cout<<"Total Running Time: "<<(double)(finish-start)/CLOCKS_PER_SEC<<"s"<<endl;
}


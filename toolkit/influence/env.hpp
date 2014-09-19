#include <vector>
#include <iostream>
#include <map>
#include <string.h>
using namespace std;




class env
{
public:
	
	vector<int> degree;
	string INPUT_DOC;
	string OUTPUT_DEGREE;
	
	env()
	{
		INPUT_DOC="/home/qicong/saedb/build/toolkit/influence/input/alledge.txt";
		OUTPUT_DEGREE="/home/qicong/saedb/build/toolkit/influence/output/degree.txt";
	}	
	
	friend std::ostream & operator<< (std::ostream & output, const env &v) 
	{
		output<<"-------------Current Parameters-------------"<<endl;
		output<<"Input document             : "<<v.INPUT_DOC<<std::endl;
		output<<"Output degree		    : "<<v.OUTPUT_DEGREE<<std::endl;
		output<<"--------------------------------------------"<<endl;
		return output;  
	}
	void AllocHeap();
	void ReleaseHeap();
	
};


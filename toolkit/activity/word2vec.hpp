#include <iostream>
#include <cstring>
#include <map>
#include <vector>
using namespace std;

// Model is the Word2vec model.
class word2vec{
public:
    int Layer1Size;
    map<string,int> Vocab;
    vector<double> data;
    word2vec(){}
    word2vec(int l,int v)
    {
        Layer1Size=l;
        data.resize(l*v);
    }
    void setVector(int k,vector<double> vec)
    {
        int begin=(k-1)*Layer1Size;
        for(int i=0;i<vec.size();i++,begin++)
            data[begin]=vec[i];
    }
    vector<double> getVector(int k)
    {
        return vector<double>(data.begin()+(k-1)*Layer1Size,data.begin()+k*Layer1Size);
    }

};


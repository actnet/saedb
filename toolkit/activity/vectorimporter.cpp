
#include "vectorimporter.hpp"


vector<string> &split(const string &s, char delim, vector<std::string> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}

double Snrm2(vector<double> vec)
{
    double s=0.0;
    for(int i=0;i<vec.size();i++)
    {
        s+=vec[i]*vec[i];
    }
    s/=vec.size();
    return s;
}

void Normalize(vector<double>& vec)
{
    double w=Snrm2(vec);
    for(int i=0;i<vec.size();i++)
        vec[i]/=w;
}

double Dot(vector<double> vecx, vector<double>vecy)
{
    double s=0.0;
    //have not check the dimension
    for(int i=0;i<vecx.size();i++)
    {
        s+=vecx[i]*vecy[i];
    }
    return s;
}

word2vec loadVector(string filename)
{
    ifstream fin(filename.c_str());
    string s;
    vector<string> components;

    int vocabSize, layer1Size;

    getline(fin,s);
    components=split(s,' ');
    vocabSize=atoi(components[0].c_str());
    layer1Size=atoi(components[1].c_str());
    word2vec Model(layer1Size,vocabSize);

    int line=0;
    while(getline(fin,s))
    {
        line++;
        components=split(s,' ');
        string word=components[0];
        vector<double> vec;
        for(int i=1;i<components.size();i++)
        {
            vec.push_back(atof(components[i].c_str()));
        }
        Normalize(vec);
        Model.Vocab[word]=line;
        Model.setVector(line,vec);
    }
    cout<<"read in "<<line<<" words!"<<endl;
    return Model;
}

#include "pagerank.hpp"

void PageRank::setGraphFile(string graphfile)
{
	this->graphFile = graphfile;
}

bool cmp(pair<double, string> a, pair<double, string> b)
{
    return a.first > b.first;
}

int PageRank::getPageRank(string resFile, double RESET_PROB, int itnum)
{
	try
    {
        int step = 0;
        sae::io::MappedGraph* g = sae::io::MappedGraph::Open(graphFile.c_str());
        for (auto v = g->Vertices(); v->Alive(); v->Next()) 
        {                        
            VData vd = sae::serialization::convert_from_string<VData>(v->Data());
            vd.value = 1;
            v->Data() = sae::serialization::convert_to_string<VData>(vd);
        }
        while(step++ < itnum)
        {
            for (auto v = g->Vertices(); v->Alive(); v->Next()) 
            {
                double temp = 0;
                VData vd = sae::serialization::convert_from_string<VData>(v->Data());
                for(auto e = v->InEdges(); e->Alive(); e->Next())
                {
                    double cvd = sae::serialization::convert_from_string<VData>(e->Source()->Data()).value;
                    temp = temp + cvd / e->Source() -> OutEdgeCount();
                }
                vd.value = RESET_PROB + temp * (1 - RESET_PROB);
                v->Data() = sae::serialization::convert_to_string<VData>(vd);
            }
        }
        ofstream outfile(resFile);
        double largest = -1;
        vector<string> name;
        vector<pair<double, string> > scoreList;
        for (auto v = g->Vertices(); v->Alive(); v->Next()) 
        {                        
            VData vd = sae::serialization::convert_from_string<VData>(v->Data());
            outfile << vd.name << " " << vd.value << "\n";
            scoreList.push_back(make_pair(vd.value, vd.name));
            if (vd.value >= largest)
            {
                if (vd.value > largest)
                {
                    largest = vd.value;
                    name.clear();
                }
                name.push_back(vd.name);
            }
        }
        cout<<"compute PageRank done."<<endl;
        sort(scoreList.begin(), scoreList.end(), cmp);
        printf("Nodes with largest PageRank scores:\n");
        for (unsigned int i = 0; i < 10 && i < scoreList.size(); i ++)
            printf("%s (%.5lf)\n", scoreList[i].second.c_str(), scoreList[i].first);
    }
    catch(...)
    {
        cout<<"PageRank parameter error"<<endl;
        return -1;
    }
    return 0;
}
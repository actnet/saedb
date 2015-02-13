#include "degreedistribution.hpp"

void DegreeDistribution::setGraphFile(string graphfile)
{
	this->graphFile = graphfile;
}

int DegreeDistribution::getDegreeDistribution()
{
	try
    {
        sae::io::MappedGraph* g = sae::io::MappedGraph::Open(graphFile.c_str());
        map<int, int> degreeMap;
        for (auto v = g -> Vertices(); v -> Alive(); v -> Next())
        {
            int d = v -> InEdgeCount() + v -> OutEdgeCount();
            if(degreeMap.find(d) == degreeMap.end())
            {
                degreeMap[d] = 1;
            }
            int c = degreeMap[d];
            degreeMap[d] = c + 1;
        }
        FILE* fout = fopen("../python/degree.out", "w");
        for (auto it = degreeMap.begin(); it != degreeMap.end(); it ++)
        {
            fprintf(fout, "%d %d\n", it -> first, it -> second);
        }
        fclose(fout);
        system("python ../python/degree.py"); 
    }
    catch (...)
    {
        cout<<"Degree parameter error"<<endl;
        return -1;
    }
    return 0;
}

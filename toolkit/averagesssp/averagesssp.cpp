#include "averagesssp.hpp"

void AverageSSSP::setGraphFile(string graphfile)
{
	this->graphFile = graphfile;
}

int AverageSSSP::getAverageSSSP()
{
	try
    {
        double** dist;
        double MAX = 10000000;
        int paircount = 0;
        double distance = 0;
        sae::io::MappedGraph* g = sae::io::MappedGraph::Open(graphFile.c_str());
        dist = new double*[g->VertexCount()];
        for(int i = 0; i < g->VertexCount(); i++)
        {
            dist[i] = new double[g -> VertexCount()];
            for(int j = 0; j < g->VertexCount(); j++)
            {
                dist[i][j] = MAX;
            }            
        }
        for (auto v = g->Vertices(); v->Alive(); v->Next()) 
        {
            for(auto e = v->OutEdges(); e->Alive(); e->Next())
            {
                dist[v->GlobalId()][e->Source()->GlobalId()] = sae::serialization::convert_from_string<EData>(e->Data()).attribute[0];                
            }
        }
        int maxIter = g->VertexCount() / 1000;
        int lastIter = -10;
        for(int k = 0; k < g->VertexCount() / 1000; k++)
        {
            if (k * 100 / maxIter >= lastIter + 10)
            {
                lastIter = k * 100 / maxIter;
                printf("Processing %d%%...\n", lastIter);
            }
            for(int i = 0; i < g->VertexCount(); i++)
            {
                for(int j = 0; j < g->VertexCount(); j++)
                {
                    if(dist[i][j] > dist[i][k] + dist[k][j])
                    {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
        for(int i = 0; i < g->VertexCount(); i++)
        {
            for(int j = 0; j < g->VertexCount(); j++)
            {
                if(dist[i][j] < MAX)
                {
                    paircount ++;
                    distance += dist[i][j];
                }
            }
        }
        if(paircount > 0)
        {            
            cout<<"Average SSSP: " << distance / paircount << endl;
        }
        else
        {
            cout<<"Average SSSP: " << 0 << endl;
        }
    }
    catch(...)
    {
        cout<<"AverageSSSP parameter error"<<endl;
        return -1;
    }
    return 0;
}
#include "degreecentrality.hpp"

void DegreeCentrality::setGraphFile(string graphfile)
{
	this->graphFile = graphfile;
}

int DegreeCentrality::getDegreeCentrality()
{
	try
    {
        int maxdegree = 0;
        double degreecentrality = 0;
        sae::io::MappedGraph* g = sae::io::MappedGraph::Open(graphFile.c_str());
        for (auto v = g->Vertices(); v->Alive(); v->Next()) 
        {
            if(v->InEdgeCount() + v->OutEdgeCount() > maxdegree)
            {
                maxdegree = v->InEdgeCount() + v->OutEdgeCount();
            }
        }
        for (auto v = g->Vertices(); v->Alive(); v->Next()) 
        {
            degreecentrality += maxdegree - v->InEdgeCount() - v->OutEdgeCount();
        }
        degreecentrality /= (g->VertexCount() - 1) * (g->VertexCount() - 2);
        cout<<"degree centrality: " << degreecentrality << endl;
    }
    catch(...)
    {
        cout << "degree centrality parameter error" << endl;
        return -1;
    }
    return 0;
}
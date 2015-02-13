#include "networkconstraints.hpp"

void NetworkConstraints::setGraphFile(string graphfile)
{
	this->graphFile = graphfile;
}

int NetworkConstraints::getNetworkConstraints(string resFile)
{
	try
    {
        sae::io::MappedGraph* g = sae::io::MappedGraph::Open(graphFile.c_str());
        for (auto e = g->Edges(); e->Alive(); e->Next()) 
        {
            EData ed = sae::serialization::convert_from_string<EData>(e->Data());
            ed.value = 0;
            for(auto es = e->Source()->OutEdges(); es->Alive(); es->Next())
            {
                for(auto ee = es->Target()->OutEdges(); ee->Alive(); ee->Next())
                {
                    if (ee->Target()->GlobalId() == e->Target()->GlobalId())
                    {
                        ed.value += sae::serialization::convert_from_string<EData>(es->Data()).attribute[0] * 
                        sae::serialization::convert_from_string<EData>(ee->Data()).attribute[0];
                        break;
                    }
                }
            }
            e->Data() = sae::serialization::convert_to_string<EData>(ed);     
        }
        ofstream outfile(resFile);
        for (auto v = g->Vertices(); v->Alive(); v->Next()) 
        {
            double value = 0;
            VData vd = sae::serialization::convert_from_string<VData>(v->Data());
            for(auto e = v->OutEdges(); e->Alive(); e->Next())
            {
                value += sae::serialization::convert_from_string<EData>(e->Data()).value;
            }
            if(v->OutEdgeCount() > 0)
            {
                outfile << vd.name << "\t" << value / v->OutEdgeCount() <<"\n";
            }
            else
            {
                outfile << vd.name << "\t" << 0 <<"\n";
            }
        }
        cout<<"compute Network Constraints done."<<endl;
    }
    catch(...)
    {
        cout << "Network Constraints parameter error" << endl;
        return -1;
    }
    return 0;
}
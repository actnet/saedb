#include "sssp.hpp"

void SSSP::setGraphFile(string graphfile)
{
	this->graphFile = graphfile;
}

int SSSP::getSSSP(string source, int least, string resFile)
{
	try
    {
        double MAX = 10000000;
        bool flag = false;
        sae::io::MappedGraph* g = sae::io::MappedGraph::Open(graphFile.c_str());
        string centerid = source.c_str();
        vector<EData> edgeList;
        vector<VData> vertexList;
        for (auto e = g -> Edges(); e -> Alive(); e -> Next())
        {
            for (unsigned int i = edgeList.size(); i <= e -> GlobalId(); i ++)
            {
                EData e;
                edgeList.push_back(e);
            }
            edgeList[e -> GlobalId()] = sae::serialization::convert_from_string<EData>(e -> Data());     
        }
        for (auto v = g->Vertices(); v->Alive(); v->Next())
        {                        
            VData vd = sae::serialization::convert_from_string<VData>(v->Data());
            if(vd.name == centerid)
            {
                vd.value = 0;
                flag = true;
            }
            else
            {
                vd.value = MAX;
            }
            v->Data() = sae::serialization::convert_to_string<VData>(vd);
        }
        for (auto v = g -> Vertices(); v -> Alive(); v -> Next())
        {
            for (unsigned int i = vertexList.size(); i <= v -> GlobalId(); i ++)
            {
                VData v;
                vertexList.push_back(v);
            }
            vertexList[v -> GlobalId()] = sae::serialization::convert_from_string<VData>(v -> Data());
        }

        if(!flag)
        {
            cout<<"Error! Can not find the source node!"<<endl; 
            return -1;
        }
        int maxIter = g->VertexCount() / 50 - 1;
        int lastIter = -10;
        for(int i = 0; i < maxIter; i++)
        {
            if (i * 100 / maxIter >= lastIter + 10)
            {
                lastIter = i * 100 / maxIter;
                printf("Processing %d%%...\n", lastIter);
            }
            for (auto e = g->Edges(); e->Alive(); e->Next()) 
            {
                EData edge = edgeList[e -> GlobalId()];
                double length = edge.attribute[0];
                VData vs = vertexList[e -> Source() -> GlobalId()];
                VData vt = vertexList[e -> Target() -> GlobalId()];
                {
                    vertexList[e -> Target() -> GlobalId()].value = vs.value + length;
                }
            }
        }
        ofstream outfile(resFile);
        double len = -1;
        vector<string> name;
        for (auto v = g->Vertices(); v->Alive(); v->Next()) 
        {                        
            //v -> Data() = sae::serialization::convert_to_string<VData>(vertexList[v -> GlobalId()]);
            VData vd = vertexList[v -> GlobalId()];
            //VData vd = sae::serialization::convert_from_string<VData>(v->Data());
            outfile << vd.name << "\t" << vd.value << "\n";
            if ((len == -1 || vd.value <= len) && (vd.value > 0) && (vd.value >= least))
            {
                if (len == -1 || vd.value < len)
                {
                    len = vd.value;
                    name.clear();
                }
                name.push_back(vd.name);
            }
        }

        if (len == -1 || len == MAX)
        {
            printf("Can not find any nodes\n");
            return -1;
        }
        cout << "Nearest nodes: " << " (length = " << len << ")" << endl;
        for (unsigned int i = 0; i < name.size(); i ++)
        {
            printf("%s\n", name[i].c_str());
        }
        cout << "compute SSSP done."<<endl;
    }
    catch(...)
    {
        cout<<"SSSP parameter error"<<endl;
        return -1;
    }
    return 0;
}

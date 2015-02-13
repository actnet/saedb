#include "commonnb.hpp"

void CommonNB::setGraphFile(string graphfile)
{
	this->graphFile = graphfile;
}

int CommonNB::getCommonNB(string resFile)
{
	try
    {
        sae::io::MappedGraph* g = sae::io::MappedGraph::Open(graphFile.c_str());
        //FILE* fout = fopen("c.txt", "w");
        ofstream outfile(resFile);
        for (auto a = g -> Vertices(); a -> Alive(); a -> Next())
        {
            bool flag = true;
            VData va = sae::serialization::convert_from_string<VData>(a -> Data());
            set<int> cset;
            for (auto e = a -> OutEdges(); e -> Alive(); e -> Next())
            {
                auto b = e -> Target();
                VData vb = sae::serialization::convert_from_string<VData>(b -> Data());
                for (auto ee = b -> InEdges(); ee -> Alive(); ee -> Next())
                {
                    auto c = ee -> Source();
                    if (c -> GlobalId() == a -> GlobalId())
                        continue;
                    if (cset.count(c -> GlobalId()) > 0)
                        continue;
                    if (flag)
                    {
                        outfile << va.name << ":";
                        flag = false;
                    }
                    cset.insert(c -> GlobalId());
                    VData vc = sae::serialization::convert_from_string<VData>(c -> Data());
                    outfile << " " << vc.name;
                    //fprintf(fout, "%s %s %s\n", va.name.c_str(), vb.name.c_str(), vc.name.c_str());
                }
            }
            if (! flag)
                outfile << endl;
        }
        //fclose(fout);
    }
    catch (...)
    {
        cout << "Common Neighbors parameter error" << endl;
        return -1;
    }
    return 0;
}

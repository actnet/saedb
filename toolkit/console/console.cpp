#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <cstdio>

#include "storage/mgraph.hpp"
#include "computing/computing.hpp"

#include "testing/testharness.hpp"
#include "gflags/gflags.h"

#include "averagesssp/averagesssp.hpp"
#include "commonnb/commonnb.hpp"
#include "degreecentrality/degreecentrality.hpp"
#include "degreedistribution/degreedistribution.hpp"
#include "networkconstraints/networkconstraints.hpp"
#include "pagerank/pagerank.hpp"
#include "sssp/sssp.hpp"
#include "model/model.hpp"


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

map<string, double> pagerankconfig;

int ReadConfigFile(string path)
{
    /*init*/
    pagerankconfig["RESET_PROB"] = 0.15;
    pagerankconfig["IT_NUM"] = 30;
    /*read*/
    map<string, double> * currentconfig;
    ifstream configfile(path);
    string line;
    vector<string> row;
    while(getline(configfile,line))
    {
        try
        {
            if(line.find("[") != -1 && line.find("]") != -1)
            {
                if (strcmp(line.c_str(), "[pagerank]") == 0)
                {
                    currentconfig = &pagerankconfig;
                    continue;
                }
                /*add something*/
                else
                {
                    break;
                }
            }
            row = split(line, ' ');
            (*currentconfig)[row[0]] = atof(row[1].c_str());
            //cout<<row[0]<<"  "<<row[1]<<endl;
        }
        catch(...)
        {
            cout<<"config file error" << endl;
            break;
        }
    }
    return 0;
}


int ShowUsage()
{
    printf("Social Analytic Engine (SAE) v0.1                               \n");
    printf("     by KEG, Tsinghua University                                \n");
    printf("                                                                \n");
    printf("Usage: console -[options] <parameters>                          \n");
    printf("options include -bg -pr -sp -dc -nc -asp                        \n");
    printf("                                                                \n");
    //printf("##############################################################  \n");
    printf("  -bg v_dir e_dir g_dir       : Build the graph with vertices from v_dir and edges from e_dir, save the graph to g_dir\n");
    printf("  -dd g_dir                   : Show the degree distribution of the graph from g_dir");
    printf("  -pr c_dir g_dir r_dir       : PageRank on the graph from g_dir, save the results to r_dir, c_dir is config file\n");
    printf("  -sp c_dir g_dir s_id r_dir  : Single source shortest path on the graph from g_dir, start from the vertex s_id, save the results to r_dir, c_dir is config file\n");
    printf("  -dc c_dir g_dir             : Degree centrality of the graph from g_dir, c_dir is config file\n");
    printf("  -nc c_dir g_dir r_dir       : Network Constraints on the graph from g_dir, save the results to r_dir, c_dir is config file\n");
    printf("  -asp g_dir                  : Average shortest paths on the graph from g_dir");
    //printf("##############################################################  \n");
    printf("\n");
    return 0;
}

int BuildGraph(string vertexFile, string edgeFile, string graphFile)
{
    try
    {
        sae::io::GraphBuilder<double> builder;
        map<string, int> vertextypedict;
        map<string, int> edgetypedict;
        map<string, int> vertexiddict;
        string line;
        ifstream vertexfile(vertexFile);
        int id = 0;
        while(getline(vertexfile,line))
        {
            vector<string> row;
            row = split(line, ' ');
            if(row.size() < 2)
                return -1;
            if(vertextypedict.find(row[0]) == vertextypedict.end())
            {
                builder.AddVertexDataType(row[0].c_str());
                vertextypedict[row[0]] = 1;
            }
            VData vdata;
            vdata.name = row[1].c_str();
            for(int i = 2; i < row.size(); i++)
                vdata.attribute.push_back(atof(row[i].c_str()));
            builder.AddVertex(id, vdata, row[0].c_str());
            vertexiddict[row[1].c_str()] = id;
            id ++;
        }
        ifstream edgefile(edgeFile);
        while(getline(edgefile,line))
        {
            vector<string> row;
            row = split(line, ' ');
            if(row.size() < 3)
                return -1;
            if(edgetypedict.find(row[0]) == edgetypedict.end())
            {
                builder.AddEdgeDataType(row[0].c_str());
                edgetypedict[row[0]] = 1;
            }
            EData edata;
            for(int i = 3; i < row.size(); i++)
                edata.attribute.push_back(atof(row[i].c_str()));
            if (row.size() <= 3)
                edata.attribute.push_back(1);
            builder.AddEdge(vertexiddict[row[1].c_str()], vertexiddict[row[2].c_str()], edata, row[0].c_str());
        }
        builder.Save(graphFile.c_str());
        sae::io::MappedGraph* g = sae::io::MappedGraph::Open(graphFile.c_str());
        cout<<"build graph done."<<endl;
        printf("The graph is ready!\n");
        printf("#nodes: %d, #edges: %d\n", (int) g -> VertexCount(), (int) g -> EdgeCount());
    }
    catch(...)
    {
        cout<<"parameter error" << endl;
    }
    return 0;
}

int getDegreeDistribution(string graphFile)
{
    DegreeDistribution instance;
    instance.setGraphFile(graphFile);
    if(instance.getDegreeDistribution() == -1)
    {
        ShowUsage();
    }
    return 0;
}

int getPageRank(string graphFile, string resFile)
{
    PageRank instance;
    instance.setGraphFile(graphFile);
    if(instance.getPageRank(resFile, pagerankconfig["RESET_PROB"], pagerankconfig["IT_NUM"]) == -1)
    {
        ShowUsage();
    }
    return 0;
}

int getSSSP(string graphFile, string source, int least, string resFile)
{
    SSSP instance;
    instance.setGraphFile(graphFile);
    if(instance.getSSSP(source, least, resFile) == -1)
    {
        ShowUsage();
    }
    return 0;
}

int getDegreeCentrality(string graphFile)
{
    DegreeCentrality instance;
    instance.setGraphFile(graphFile);
    if(instance.getDegreeCentrality() == -1)
    {
        ShowUsage();
    }
    return 0;
}

int getNetworkConstraints(string graphFile, string resFile)
{
    NetworkConstraints instance;
    instance.setGraphFile(graphFile);
    if(instance.getNetworkConstraints(resFile) == -1)
    {
        ShowUsage();
    }
    return 0;
}

int getAverageSSSP(string graphFile)
{
    AverageSSSP instance;
    instance.setGraphFile(graphFile);
    if(instance.getAverageSSSP() == -1)
    {
        ShowUsage();
    }
    return 0;
}

int getCommonNB(string graphFile, string resFile)
{
    AverageSSSP instance;
    instance.setGraphFile(graphFile);
    if(instance.getAverageSSSP() == -1)
    {
        ShowUsage();
    }
    return 0;
}

int main(int argc, char** argv) 
{
    if(argc < 2)
    {
        ShowUsage();
        cout<<"parameter error"<<endl;
        return 0;
    }
    int i = 1;
    while (i < argc)
    {
        if (strcmp(argv[i], "-bg") == 0)
        {
            if (i + 3 >= argc)
            {
                ShowUsage();
                cout << "Build graph parameter error!" << endl;
                return 0;
            }
            //ReadConfigFile(argv[i + 1]);
            string vertexFile = argv[i + 1];
            string edgeFile = argv[i + 2];
            string graphFile = argv[i + 3];
            BuildGraph(vertexFile, edgeFile, graphFile);
            i += 4;
            continue;
        }
        if (strcmp(argv[i], "-pr") == 0)
        {
            if (i + 3 >= argc)
            {
                ShowUsage();
                cout << "PageRank parameter error!" << endl;
                return 0;
            }
            ReadConfigFile(argv[i + 1]);
            getPageRank(argv[i + 2], argv[i + 3]);
            i += 4;
            continue;
        }
        if (strcmp(argv[i], "-sp") == 0)
        {
            if (i + 5 >= argc)
            {
                ShowUsage();
                cout << "SSSP parameter error!" << endl;
                return 0;
            }
            ReadConfigFile(argv[i + 1]);
            getSSSP(argv[i + 2], argv[i + 3], atoi(argv[i + 4]), argv[i + 5]);
            i += 6;
            continue;
        }
        if (strcmp(argv[i], "-dc") == 0)
        {
            if (i + 2 >= argc)
            {
                ShowUsage();
                cout << "DegreeCentrality parameter error!" << endl;
                return 0;
            }
            ReadConfigFile(argv[i + 1]);
            getDegreeCentrality(argv[i + 2]);
            i += 3;
            continue;
        }
        if (strcmp(argv[i], "-nc") == 0)
        {
            if (i + 3 >= argc)
            {
                ShowUsage();
                cout << "NetworkConstraint parameter error!" << endl;
                return 0;
            }
            ReadConfigFile(argv[i + 1]);
            getNetworkConstraints(argv[i + 2], argv[i + 3]);
            i += 4;
            continue;
        }
        if (strcmp(argv[i], "-dd") == 0)
        {
            if (i + 1 >= argc)
            {
                ShowUsage();
                cout << "DegreeDistribution parameter error!" << endl;
                return 0;
            }
            getDegreeDistribution(argv[i + 1]);
            i += 2;
            continue;
        }
        if (strcmp(argv[i], "-asp") == 0)
        {
            if (i + 1 >= argc)
            {
                ShowUsage();
                cout << "AverageShortestPath parameter error!" << endl;
                return 0;
            }
            getAverageSSSP(argv[i + 1]);
            i += 2;
            continue;
        }
        if (strcmp(argv[i], "-cn") == 0)
        {
            if (i + 2 >= argc)
            {
                ShowUsage();
                cout << "CommonNeighbor parameter error!" << endl;
                return 0;
            }
            getCommonNB(argv[i + 1], argv[i + 2]);
            i += 3;
            continue;
        }
        cout<<"command not found"<<endl;
        ShowUsage();
        break;
    }
}


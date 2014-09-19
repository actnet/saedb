#include <cmath>
#include <fstream>
#include <sstream>
#include "computing/computing.hpp"
#include "enron_instance.hpp"
#include "env.hpp"
env env_inst;

vector<pair<int,int> > sort_pool;
void sort_pair(vector<pair<int,int>>& vec);
vector<string> line_tokenize(string a, string seps);
vector<string> component_tokenize(string a, string seps);
typedef int message_data_type;
typedef saedb::sae_graph graph_type;


class degree:
public saedb::IAlgorithm<graph_type, double, message_data_type>
{
public:
	
	void init(icontext_type& context, vertex_type& vertex, const message_type& msg) {
		vertex_data v=vertex.parse<vertex_data>();
		
	
    	}
	edge_dir_type gather_edges(icontext_type& context,const vertex_type& vertex) const{
		
		return saedb::NO_EDGES;
	}	
	
	double gather(icontext_type& context, const vertex_type& vertex,
                 edge_type& edge) const 
	{
		return 0;
	    	
	}

	
	void apply(icontext_type& context, vertex_type& vertex,
               const gather_type& total)
    	{
		sort_pool.push_back(make_pair(vertex.parse<vertex_data>().id,vertex.num_in_edges()+vertex.num_out_edges()));
		
	}
	
	edge_dir_type scatter_edges(icontext_type& context,
                                const vertex_type& vertex) const{
		return saedb::NO_EDGES;
	}

	
	 void scatter(icontext_type& context, const vertex_type& vertex,
                 edge_type& edge) const
	{
	}
};
void  BuildGraph(string file)
{
	sae::io::GraphBuilder<int> b;
        b.AddVertexDataType("Vertex");
        b.AddEdgeDataType("Edge");
	int eid=0;
	
	string s;
	ifstream fin(env_inst.INPUT_DOC);
	vector<string> components;
	while(getline(fin,s))
	{
		
		components=component_tokenize(s,"#");
		int sid=atoi(components[2].c_str());
		int rid=atoi(components[3].c_str());
		b.AddVertex(sid,vertex_data(sid),"Vertex");
		b.AddVertex(rid,vertex_data(rid),"Vertex");
		b.AddEdge(sid,rid,edge_data(eid++),"Edge");
		
	}
	cout<<"reading "<<eid<<" lines!"<<endl;
	fin.close();

	system("mkdir /home/qicong/saedb/build/toolkit/influence/graph");
	
	b.Save(file.c_str());
	
	
}

void OutputDegree(string file)
{
	sort_pair(sort_pool);
	ofstream fout;
	fout.open(file.c_str());
	for(int i=0;i<sort_pool.size();i++)
	{
		fout<<sort_pool[i].first<<" "<<sort_pool[i].second<<endl;
	}
	fout.close();
	fout.clear();
	//call python to draw
	//system("python ./input/degree.py ./output/degree.txt 1 10 0 1.0");
}
void Output()
{
	system("mkdir /home/qicong/saedb/build/toolkit/influence/output");
	OutputDegree(env_inst.OUTPUT_DEGREE);
}
void run_enron()
{
	
	BuildGraph("/home/qicong/saedb/build/toolkit/influence/graph/graph_enron");
        cout << "Generating Graph Data Done. " << endl;
    	
	graph_type enron_graph;
	enron_graph.load_format("/home/qicong/saedb/build/toolkit/influence/graph/graph_enron");
	cout <<"Loading Graph Done."<<endl;
	cout<<"num of vertexes :"<<enron_graph.num_local_vertices()<<endl;
	
	
	cout<<"Process Start..."<<endl;
	//Cal degree	
	saedb::IEngine<degree> *engine_degree = new saedb::EngineDelegate<degree>(enron_graph);	
	engine_degree->signalAll();
	engine_degree->start();
	delete engine_degree;
	cout<<"Process done"<<endl;
	
	Output();
        
	
	
}

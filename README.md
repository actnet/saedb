SAE: Social Analytic Engine
============
We present a Social Analytic Engine (SAE) for analyzing and mining large social network. The figure below
shows the architecture of SAE. The cornerstone of the analytic engine is a distributed graph database, which provides storage for the networking data. On the top of the database, there are three core components: network integration, social network analysis, and distributed machine learning. 

![](https://github.com/actnet/saedb/blob/master/figs/SAE_framework.png)

The **network integration** component supports to integrate entities extracted from different networks. For example, in academia, an author may have profile pages on Google Scholar, AMiner, and LinkedIn, but with different accounts. Automatically recognizing and integrating those profile pages can benefit many application such as expert finding and influence analysis.

The **social network analysis** component is our major technical contribution. It first provides basic analyses for network characteristics, including macro-level properties such as density, diameter, degree distribution, community partition, and also micro-level properties such as centrality, homophily, reciprocity, prestige, and reachability for specific nodes. Moreover, we have designed and implemented several novel technologies for social influence analysis, structural hole spanner detection, and social tie mining. More specifically, social influence aims to quantify the influential strength between users from different angles (topics) in a large social network. Structural hole spanner detection tries to recognize structural hole spanners who control the information flow in the social network. Social tie mining tries to reveal fundamental factors that form the different types of social relationships.

The **machine learning component** supports to incorporate various social based factors derived from the above social network analysis component into machine learning models.  

####Requirements

We do regular developments with Linux and Mac OS X environments. Here's a list of our prerequists:

	CMake 2.8+
	g++ 4.8 or clang 3.3
	protobuf 2.4+ (for RPC)
	zeromq 3.2+ (for PRC)

On Linux, it's easy to get those softwares and libraries with your distribution's package manager.

On Mac OS X, please install the lastest XCode Command Line Tools and homebrew. Then you can install protobuf and zeromq with brew. We use libc++ by default on Mac OS X.

####Build
We recommend to build the project outside the source tree. To do this, please go to the root of this project and execute the following commands:

	mkdir build
	cd build
	cmake ..
	make

Then you can do some testing with:

	ctest

If something goes wrong with your build system, it's easy to delete the `build` directory and restart.

####Acknowlegement
The system was developed by Tsinghua University Knowledge Engineering Group (KEG), sponsored by Huawei Technologies Co., Ltd.

#### How to build your own system based on SAE
Based on SAE, users are able to build their own social network analytic services. Generally, SAEDB project has provided a data process service, and also the RPC service for the front-end of the custom system. Here, we give an example system to demonstrate how to build a custom system: [https://github.com/actnet/actnetdemo](ActivityNet).  
###How to build a graph  
#####1. Define vertex type and edge data type  
```
struct VData{
    int data;
};
struct EData{
    int data;
};
namespace sae {
    namespace serialization {
        namespace custom_serialization_impl {
            template <>
            struct serialize_impl<sae::serialization::OSerializeStream, VData> {
                static void run(sae::serialization::OSerializeStream& ostr, const VData& a) {
                    ostr << a.data
                }
            };

            template <>
            struct deserialize_impl<sae::serialization::ISerializeStream, VData> {
                static void run(sae::serialization::ISerializeStream& istr, VData& a) {
                    istr >> a.data;
                }
            };
            
            template <>
            struct serialize_impl<sae::serialization::OSerializeStream, EData> {
                static void run(sae::serialization::OSerializeStream& ostr, const EData& a) {
                    ostr << a.data
                }
            };

            template <>
            struct deserialize_impl<sae::serialization::ISerializeStream, EData> {
                static void run(sae::serialization::ISerializeStream& istr, EData& a) {
                    istr >> a.data;
                }
            };
        }
    }
}
```
#####2. Define graph builder
```
sae::io::GraphBuilder<double> builder
```
#####3. Add vertex data type and edge data type
```
builder.AddVertexDataType("VData");
builder.AddEdgeDataType("EData");
```
#####4. Add vertex data and edge data
```
builder.AddVertex(0,  VData(1), "VData");
builder.AddVertex(1,  VData(1), "VData");
builder.AddEdge(0, 1, EData{0}, "EData");
```
###How to save a graph
```	
sae::io::GraphBuilder<double> builder
builder.Save(graphpath.c_str());
```
###How to use your graph
#####1. Load a graph
```
sae::io::MappedGraph* g = sae::io::MappedGraph::Open(savepath.c_str());
```
#####2. Get vertex count and edge count
```
int vertexcount = g->VertexCount();//get vertex count
int edgecount = g->EdgeCount();//get edge count
```
#####3. Traverse all vertices and get their out edges and in edges
```
for (auto v = g->VerticesOfType("VData"); v->Alive(); v->NextOfType()) {
   VData vData = sae::serialization::convert_from_string<VData>(v->Data());
   EData outEdgeData = sae::serialization::convert_from_string<VData>(v->OutEdges()->Data());
   EData inEdgeData = sae::serialization::convert_from_string<VData>(v->InEdges()->Data());
}
```
#####4. Traverse vextex v's out edges and get their end vertices
```
for (auto e = v->OutEdges(); e->Alive(); e->Next()) {
   EData eData = sae::serialization::convert_from_string<EData>(e->Data());
   VData vData = sae::serialization::convert_from_string<VData>(e->Target()->Data());
}
```




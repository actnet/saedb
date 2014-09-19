SAE: Social Analytic Engine
============
We present a Social Analytic Engine (SAE) for analyzing and mining large social network. Figure 1
shows the architecture of SAE. The cornerstone of the analytic engine is a distributed graph database, which provides storage for the networking data. On the top of the database, there are three core components: network integration, social network analysis, and distributed machine learning. 

![](http://keg.cs.tsinghua.edu.cn/jietang/publications/KDD13-poster-SAE.pdf)

The *network integration* component supports to integrate entities extracted from different networks. For example, in academia, an author may have profile pages on Google Scholar, AMiner, and LinkedIn, but with different accounts. Automatically recognizing and integrating those profile pages can benefit many application such as expert finding and influence analysis.

The *social network analysis* component is our major technical contribution. It first provides basic analyses for network characteristics, including macro-level properties such as density, diameter, degree distribution, community partition, and also micro-level properties such as centrality, homophily, reciprocity, prestige, and reachability for specific nodes. Moreover, we have designed and implemented several novel technologies for social influence analysis, structural hole spanner detection, and social tie mining. More specifically, social influence aims to quantify the influential strength between users from different angles (topics) in a large social network. Structural hole spanner detection tries to recognize structural hole spanners who control the information flow in the social network. Social tie mining tries to reveal fundamental factors that form the different types of social relationships.

The *machine learning component* supports to incorporate various social based factors derived from the above social network analysis component into machine learning models.  

Requirements
============

We do regular developments with Linux and Mac OS X environments. Here's a list of our prerequists:

	CMake 2.8+
	g++ 4.8 or clang 3.3
	protobuf 2.4+ (for RPC)
	zeromq 3.2+ (for PRC)

On Linux, it's easy to get those softwares and libraries with your distribution's package manager.

On Mac OS X, please install the lastest XCode Command Line Tools and homebrew. Then you can install protobuf and zeromq with brew. We use libc++ by default on Mac OS X.

Build
=====

We recommend to build the project outside the source tree. To do this, please go to the root of this project and execute the following commands:

	mkdir build
	cd build
	cmake ..
	make

Then you can do some testing with:

	ctest

If something goes wrong with your build system, it's easy to delete the `build` directory and restart.

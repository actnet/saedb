#pragma once
#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <algorithm>

#include "storage/mgraph.hpp"
#include "computing/computing.hpp"

#include "testing/testharness.hpp"
#include "gflags/gflags.h"
#include "model/model.hpp"

using namespace std;

class PageRank
{
public:
	PageRank() {}
	~PageRank() {}
public:
	string graphFile;
public:
	void setGraphFile(string graphfile);
	int getPageRank(string resFile, double RESET_PROB, int itnum);
};
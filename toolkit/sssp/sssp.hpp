#pragma once
#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <cstdio>

#include "storage/mgraph.hpp"
#include "computing/computing.hpp"

#include "testing/testharness.hpp"
#include "gflags/gflags.h"
#include "model/model.hpp"

using namespace std;

class SSSP
{
public:
	SSSP() {}
	~SSSP() {}
public:
	string graphFile;
public:
	void setGraphFile(string graphfile);
	int getSSSP(string source, int least, string resFile);
};
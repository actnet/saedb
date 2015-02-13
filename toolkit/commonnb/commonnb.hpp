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

class CommonNB
{
public:
	CommonNB() {}
	~CommonNB() {}
public:
	string graphFile;
public:
	void setGraphFile(string graphfile);
	int getCommonNB(string resFile);
};
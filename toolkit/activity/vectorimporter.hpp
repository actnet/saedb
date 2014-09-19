#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "storage/mgraph.hpp"
#include "word2vec.hpp"
#include "computing/computing.hpp"
#include "json/json.h"

typedef saedb::sae_graph graph_type;
typedef saedb::empty message_data_type;

using namespace std;

vector<string> &split(const string &s, char delim, vector<std::string> &elems);

vector<string> split(const string &s, char delim);

double Snrm2(vector<double> vec);

void Normalize(vector<double>& vec);

double Dot(vector<double> vecx, vector<double>vecy);

word2vec loadVector(string filename);

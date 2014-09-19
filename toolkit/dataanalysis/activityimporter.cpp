#include <fstream>
#include <sstream>
#include <cstdio>
#include <algorithm>
#include <vector>

#include "storage/mgraph.hpp"
#include "computing/computing.hpp"
#include "activity.hpp"
#include "activityanalysis.hpp"

using namespace std;

typedef saedb::sae_graph graph_type;
typedef saedb::empty message_data_type;

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

string deleteSpace(string &content){
    string res = "";
    vector<string> row = split(content, ' ');
    for(vector<string>::iterator it  = row.begin(); it != row.end(); it++)
        res.append(*it);
    return res;
}

void loadInstance(string path, map<string, map<string, int>> &actuser){
    ifstream file(path);
    string line;
    vector<string> row;
    while(getline(file,line))
    {
        row = split(line, '\t');
        vector<string> activities = split(row[0], '|');
        for(int i = 0; i < activities.size(); i++){
            if(actuser.find(activities[i]) == actuser.end())
            {
                map<string, int> user;
                user[row[1]] = 1;
                actuser[activities[i]] = user;
            }
            else{
                if(actuser[activities[i]].find(row[1]) == actuser[activities[i]].end())
                    actuser[activities[i]][row[1]] = 1;
                else
                    actuser[activities[i]][row[1]] = actuser[activities[i]][row[1]] + 1;
            }
        }
    }
}


bool compare(Activity i, Activity j){ return i.trendency > j.trendency; }

void loadFollowUser(string hashpath, string followpath, string savepath, map<string, vector<string>> &followuser){
    /******************read hash file******************/
    ifstream hashfile(hashpath);
    string line;
    int count = 0;
    map<int, string> hashuser;
    while(getline(hashfile,line)){
        hashuser[count] = split(line, '\n')[0];
        count++;
    }
    /*****************read follow file****************/
    int wcount = 0;
    ifstream followfile(followpath);
    getline(followfile,line);
    vector<string> row;
    while(getline(followfile,line)){
        cout << "w: "<<wcount++<<"\n";
        row = split(line, '\t');
        vector<string> friends;
        for(int i = 2; i < row.size();i = i + 2){
            friends.push_back(hashuser[atoi(row[i].c_str())]);
        }
        followuser[hashuser[atoi(row[0].c_str())]] = friends;
    }
    /****************************************/
    sae::io::MappedGraph* g = sae::io::MappedGraph::Open(savepath.c_str());
    vector<Activity> result;
    cout << "loaded, n: " << g->VertexCount() << ", m:" << g->EdgeCount() << endl;
    int ncount = 0;
    ofstream allfile ("analysis_result_all.txt");
    for (auto vs = g->VerticesOfType("Activity"); vs->Alive(); vs->NextOfType()) {
        cout << "n: "<<ncount++ << "\n";
        Activity vd = parse<Activity>(vs->Data());
        ActivityAnalysis analysis;
        analysis.name = vd.name;
        map<string, int> users;
        allfile<<vd.name<<"\t";
        for(auto ei = vs->InEdges(); ei->Alive(); ei->Next()){
            users[parse<UUser>(ei->Source()->Data()).userid] = 1;
        }
        for(auto ei = vs->InEdges(); ei->Alive(); ei->Next()){
            double y = parse<UserEdge>(ei->Data()).times;
            int relatednum = 0;
            string userid = parse<UUser>(ei->Source()->Data()).userid;
            cout<<userid<<"::"<<followuser[userid].size()<<"\n";
            for(int i = 0; i < followuser[userid].size(); i++)
            {
                if(users.find(followuser[userid][i]) != users.end())
                    relatednum ++;
            }
            int sum = followuser[userid].size();
            if(sum != 0){
                double x = relatednum / (double)sum;
                analysis.addPoint(x, y);
                allfile<<"("<<x<<","<<y<<")"<<"\t";
            }
        }
        allfile<<"\n";
        //analysis.SortPoint();
        vd.trendency = analysis.compute();
        result.push_back(vd);
    }
    allfile.close();
    sort(result.begin(), result.end(), compare);
    ofstream simplefile ("analysis_result_simple.txt");
    for(int i = 0; i < result.size(); i++)
        simplefile << result[i].name<<"\t"<<result[i].trendency<<"\n";
    simplefile.close();
}

void AnalysisByFollow(string savepath, map<string, vector<string>> &followuser){
    cout<<"size:"<<followuser.size()<<"\n";
    sae::io::MappedGraph* g = sae::io::MappedGraph::Open(savepath.c_str());
    vector<Activity> result;
    cout << "loaded, n: " << g->VertexCount() << ", m:" << g->EdgeCount() << endl;
    int ncount = 0;
    ofstream allfile ("analysis_result_all.txt");
    for (auto vs = g->VerticesOfType("Activity"); vs->Alive(); vs->NextOfType()) {
        //cout << "n: "<<ncount++ << "\n";
        Activity vd = parse<Activity>(vs->Data());
        ActivityAnalysis analysis;
        analysis.name = vd.name;
        map<string, int> users;
        allfile<<vd.name<<"\t";
        for(auto ei = vs->InEdges(); ei->Alive(); ei->Next()){
            users[parse<UUser>(ei->Source()->Data()).userid] = 1;
        }
        for(auto ei = vs->InEdges(); ei->Alive(); ei->Next()){
            double y = parse<UserEdge>(ei->Data()).times;
            int relatednum = 0;
            string userid = parse<UUser>(ei->Source()->Data()).userid;
            for(int i = 0; i < followuser[userid].size(); i++)
            {
                if(users.find(followuser[userid][i]) != users.end())
                    relatednum ++;
            }
            int sum = followuser[userid].size();
            if(sum != 0){
                double x = relatednum / (double)sum;
                analysis.addPoint(x, y);
                allfile<<"("<<x<<","<<y<<")"<<"\t";
            }
        }
        allfile<<"\n";
        //analysis.SortPoint();
        vd.trendency = analysis.compute();
        result.push_back(vd);
    }
    allfile.close();
    sort(result.begin(), result.end(), compare);
    ofstream simplefile ("analysis_result_simple.txt");
    for(int i = 0; i < result.size(); i++)
        simplefile << result[i].name<<"\t"<<result[i].trendency<<"\n";
    simplefile.close();

    // ofstream allfile ("analysis_result_all.txt");
    // for(int i = 0; i < result.size(); i++){
    //     allfile << result[i].name<<"\t"<<result[i].trendency<<"\t";
    // }
    // allfile.close();
}

int main()
{
    string instancepath = "instances_large.txt";
    string hashpath = "uidlist.txt";
    string followpath = "weibo_network.txt";
    string savepath = "analysisdata/instance";
    map<string, map<string, int>> actuser;//for load in next
    map<string, vector<string>> followuser;//for load in follow
    map<string, double> actid;//index
    map<string, double> userid;//index

    // loadInstance(instancepath, actuser);
    // cout<<"load instance done."<<endl;

    // sae::io::GraphBuilder<double> builder;
    // builder.AddVertexDataType("UUser");
    // builder.AddVertexDataType("Activity");
    // builder.AddEdgeDataType("UserEdge");

    // double id = 1;
    // for(map<string, map<string, int>>::iterator it = actuser.begin(); it != actuser.end(); it++)
    // {
    //     builder.AddVertex(id, Activity{it->first}, "Activity");
    //     //cout<<it->Name<<endl;
    //     actid[it->first] = id;
    //     id++;
    // }
    // cout<<"load Activity done."<< id <<endl;
    
    // for(map<string, map<string, int>>::iterator it = actuser.begin(); it != actuser.end(); it++)
    // {
    //     map<string, int> users = it->second;
    //     for(map<string, int>::iterator st  = users.begin(); st != users.end(); st++)
    //     {
    //         if(userid.find(st->first) == userid.end()){
    //             builder.AddVertex(id, UUser{st->first}, "UUser");
    //             userid[st->first] = id;
    //             id++;
    //         }
    //         if(actid[it->first] == 0)
    //             continue;
    //         builder.AddEdge(userid[st->first], actid[it->first], UserEdge{st->second},"UserEdge");
    //     }
    // }
    // cout<<"load user done."<<endl;

    // builder.Save(savepath.c_str());
    // cout<<"build graph done."<<endl;

    // sae::io::MappedGraph* g = sae::io::MappedGraph::Open(savepath.c_str());
    // vector<Activity> result;
    // cout << "loaded, n: " << g->VertexCount() << ", m:" << g->EdgeCount() << endl;
    // int ncount = 0;
    // int scount = 0;
    // for (auto vs = g->VerticesOfType("Activity"); vs->Alive(); vs->NextOfType()) {
    //     cout << "s:"<<scount << "  n:"<<ncount++ << "\n";
    //     Activity vd = sae::serialization::convert_from_string<Activity>(vs->Data());
    //     ActivityAnalysis analysis;
    //     analysis.name = vd.name;
    //     for(auto ei = vs->InEdges(); ei->Alive(); ei->Next()){
    //         if(scount == 0)
    //             continue;
    //         double y = parse<UserEdge>(ei->Data()).times;
    //         map<string, int> friends;
    //         for(auto ev = ei->Source()->OutEdges(); ev->Alive(); ev->Next()){
    //             for(auto ea = ev->Target()->InEdges(); ea->Alive(); ea->Next()){
    //                 string friend_name = parse<UUser>(ea->Source()->Data()).userid;
    //                 friends[friend_name] = 0;
    //             }
    //         }
    //         for(auto ev = vs->InEdges(); ev->Alive(); ev->Next()){
    //             string friend_name = parse<UUser>(ev->Source()->Data()).userid;
    //             friends[friend_name] = 1;
    //         }
    //         double count = 0, num = 0;
    //         for(map<string, int>::iterator st  = friends.begin(); st != friends.end(); st++){
    //             count++;
    //             if(st->second == 1)
    //                 num++;
    //         }
    //         count--; 
    //         num--;
    //         double x = num / count;
    //         analysis.addPoint(x, y);
    //     }
    //     vd.trendency = analysis.compute();
    //     result.push_back(vd);
    //     if(ncount == 100)
    //     {
    //         ncount = 0;
    //         scount++;
    //         stringstream ss;
    //         ss<<scount; 
    //         string s1 = ss.str();
    //         sort(result.begin(), result.end(), compare);
    //         ofstream ofile ("analysisresult" + s1 +".txt");
    //         for(int i = 0; i < result.size(); i++)
    //             ofile << result[i].name<<"  "<<result[i].trendency<<"\n";
    //         ofile.close();
    //         result.clear();
    //     }
    // }
    loadFollowUser(hashpath, followpath, savepath, followuser);
    //AnalysisByFollow(savepath, followuser);
}

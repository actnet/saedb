#include <fstream>
#include <sstream>
#include <cstdio>

#include "storage/mgraph.hpp"
#include "computing/computing.hpp"
#include "json/json.h"
#include "activity.hpp"

typedef saedb::sae_graph graph_type;
typedef saedb::empty message_data_type;

class MonthConverter
{
public:
    map<string ,int> month2id;
    MonthConverter(){
        month2id["Jan"]=1;
        month2id["Feb"]=2;
        month2id["Mar"]=3;
        month2id["Apr"]=4;
        month2id["May"]=5;
        month2id["Jun"]=6;
        month2id["Jul"]=7;
        month2id["Aug"]=8;
        month2id["Sep"]=9;
        month2id["Oct"]=10;
        month2id["Nov"]=11;
        month2id["Dec"]=12;

    }
};

time_t parseTime(string &t)
{
   // "Tue Feb 28 01:51:07 +0800 2012"
    MonthConverter mc;
    struct tm stm;
    vector<string> components=split(t,' ');
    stm.tm_mday=atoi(components[2].c_str());
    stm.tm_year=atoi(components[5].c_str());
    stm.tm_mon=mc.month2id[components[1]];
    components=split(components[3],':');
    stm.tm_hour=atoi(components[0].c_str());
    stm.tm_min=atoi(components[1].c_str());
    stm.tm_sec=atoi(components[2].c_str());

    stm.tm_year -= 1900;
    stm.tm_mon --;
    stm.tm_isdst = -1;
    time_t timestamp = mktime(&stm);
    return timestamp;
}

int parseHour(string &t)
{
   // "Tue Feb 28 01:51:07 +0800 2012"
    MonthConverter mc;
    struct tm stm;
    vector<string> components=split(t,' ');
    components=split(components[3],':');
    return atoi(components[0].c_str());
}


string deleteSpace(string &content){
    string res = "";
    vector<string> row = split(content, ' ');
    for(vector<string>::iterator it  = row.begin(); it != row.end(); it++)
        res.append(*it);
    return res;
}

void loadCenter(string path, map<string, vector<string>> &center)
{
    ifstream file(path);
    string line;
    while(getline(file,line))
    {
        vector<string> row;
        row = split(line, ' ');
        center[row[0]] = row;
    }
}

void loadFilter(string path, map<string, int> &filter)
{
    ifstream file(path);
    string line;
    while(getline(file,line))
        filter[line] = 1;
}

void loadUserinfo(string path, map<string, UUser> &userinfo)
{
    ifstream file(path);
    string line;
    while(getline(file,line)){
        vector<string> row = split(line, '\t');
        UUser user;
        user.userid = row[0];
        // user.username = row[1];
        // user.userimage = row[2];
        userinfo[row[0]] = user;
    }
}

void loadJson(string path, map<string, vector<NextActivity>> &actnext, 
    map<string, vector<string>> &actpoi, map<string, int> &filter)
{
    Json::Reader reader;
    Json::Value root;

    ifstream file;
    file.open(path, ios::binary);
    if (reader.parse(file, root))
    {
        int root_size = root.size();
        for(int i = 0; i < root_size; i++)
        {
            //name
            string name = root[i]["Verb"].asString() + root[i]["Object"].asString();
            if(filter[name] != 1)
                continue;
            //poi
            vector<string> pois;
            int poi_size = root[i]["POIs"].size();
            for(int k = 0; k < poi_size; k++)
            {
                string poi = root[i]["POIs"][k]["Type"].asString();
                pois.push_back(poi);
            }
            actpoi[name] = pois;
            //nextactivity
            vector<NextActivity> nextactivities;
            int next_size = root[i]["Next"].size();
            for(int m = 0; m < next_size; m++)
            {
                NextActivity next;
                next.name = root[i]["Next"][m]["Name"].asString();
                next.dur = root[i]["Next"][m]["Gap"].asDouble();
                nextactivities.push_back(next);
            }
            actnext[name] = nextactivities;
        }
    }
    file.close();
}

void loadAllActivity(string path, vector<Activity> &activities, 
    /*map<string, vector<NextActivity>> &actnext, */map<string, map<string, int>> &actuser, 
    map<string, vector<string>> &actpoi, map<string, int> &filter){
    ifstream file(path);
    string line;
    vector<string> row;
    map<string, double> truth;
    //activity"\t"wordvector"\t"nextactivity_list"\t"instance_list
    ofstream ofile("all_activity_loc_time.txt");
    while(getline(file,line))
    {
        row = split(line, '\t');
        Activity activity;
        //name
        vector<string> title = split(row[0], ' ');
        if(title.size() == 2){
            activity.text.Verb = title[0];
            activity.text.Object = title[1];
            activity.name = activity.text.Verb + activity.text.Object;
        }
        else{
            activity.text.Verb = row[0];
            activity.text.Object = "";
            activity.name = activity.text.Verb;
        }
        //feature
        vector<string> sfeature = split(row[1], ' ');
        vector<double> dfeature;
        for(int i = 0; i < sfeature.size(); i++)
            dfeature.push_back(atof(sfeature[i].c_str()));
        activity.feature = dfeature;

        ofile << activity.name;
        // for(int i = 0; i < dfeature.size(); i++)
        //     ofile << " " << dfeature[i];
        // ofile << "\n";

        //if(filter[activity.name] != 1)
        //    continue;
        //filter[activity.name] = 2;

        //nextactivity
        // string nextstr = row[2].substr(0, row[2].length() - 1);
        // vector<string> nextsstr = split(nextstr, ';');
        // vector<NextActivity> nextactivities;
        // for(vector<string>::iterator it  = nextsstr.begin(); it != nextsstr.end(); it++){
        //     vector<string> next = split(*it, '|');
        //     if(next[1] == "暂无")
        //         break;
        //     NextActivity nextactivitiy;
        //     nextactivitiy.name = deleteSpace(next[1]);
        //     nextactivitiy.dur = atof(next[0].c_str());
        //     nextactivities.push_back(nextactivitiy);
        // }
        // actnext[activity.name] = nextactivities;
        //instance
        vector<string> instancestr = split(row[3], ';');
        vector<Instance> instances;
        map<string, int> users;
        for(vector<string>::iterator it  = instancestr.begin(); it != instancestr.end(); it++){
            vector<string> inst = split(*it, '|');
            Instance instance;
            instance.microblogid = inst[0];
            instance.userid = inst[1];
            instance.lantitude = atof(inst[2].c_str());
            instance.longtitude = atof(inst[3].c_str());
            instance.timestamp = parseTime(inst[4]);
            instance.sentiment = inst[5];
            instances.push_back(instance);
            map<string, int>::iterator ut = users.find(inst[1]);
            if (ut != users.end())
                ut->second = ut->second + 1;
            else
                users[inst[1]] = 1;
            ofile << "\t"<<parseHour(inst[4])<<"|"<<instance.lantitude<<"|"<<instance.longtitude;
        }
        ofile<<"\n";
        activity.instances = instances;
        activity.instanceNum = instances.size();
        actuser[activity.name] = users;
        if(actpoi.find(activity.name) == actpoi.end())
        {
            vector<string> pois;
            activity.pois = pois;
        }
        else
            activity.pois = actpoi[activity.name];
        activities.push_back(activity);
    }
    ofile.close();
}

void loadFeatureJson(string path, string result)
{
    Json::Reader reader;
    Json::Value root;

    ifstream file(path);
    string line;
    int i = 0;
    ofstream ofile(result);
    while(getline(file,line))
    {
        if (reader.parse(line, root))
        {   
            long long id = (long long)root["id"].asDouble();
            int reposts_count = root["reposts_count"].asInt();
            int comments_count = root["comments_count"].asInt();
            bool favorited = root["favorited"].asBool();
            ofile << id <<"\t"<<reposts_count<<"\t"<<comments_count<<"\t"<<favorited<<"\n";
        }
        cout<<i++<<"\n";
    }
    ofile.close();
    cout<<"write ok"<<"\n";
    file.close();
}

void copyFile(string path, string result)
{
    ofstream ofile(result);
    ifstream file(path);
    string line;
    ofile<<"[";
    while(getline(file,line))
    {
        ofile<<line<<"\n";
    }
    ofile<<"]";
    ofile.close();
    file.close();
    cout<<"copy ok";
}

void loadMicroFeature(string path, map<string, string> &microfeature)
{
    ifstream file(path);
    string line;
    vector<string> row;
    int i = 0;
    while(getline(file,line))
    {
        row = split(line, '\t');
        microfeature[row[0]] = row[1] + "|" +  row[2] + "|" + row[3];
        cout<<i++<<"\n";
    }
}

void loadAllActivityFeature(string micropath, string path, string result){
    ifstream file(path);
    string line;
    vector<string> row;
    map<string, string> microfeature;
    loadMicroFeature(micropath, microfeature);
    //activity"\t"wordvector"\t"nextactivity_list"\t"instance_list
    ofstream ofile(result);
    while(getline(file,line))
    {
        row = split(line, '\t');
        Activity activity;
        //name
        vector<string> title = split(row[0], ' ');
        if(title.size() == 2){
            activity.text.Verb = title[0];
            activity.text.Object = title[1];
            activity.name = activity.text.Verb + activity.text.Object;
        }
        else{
            activity.text.Verb = row[0];
            activity.text.Object = "";
            activity.name = activity.text.Verb;
        }

        ofile << activity.name;
        //instance
        vector<string> instancestr = split(row[3], ';');
        vector<Instance> instances;
        for(vector<string>::iterator it  = instancestr.begin(); it != instancestr.end(); it++){
            vector<string> inst = split(*it, '|');
            Instance instance;
            instance.microblogid = inst[0];
            instance.userid = inst[1];
            instance.lantitude = atof(inst[2].c_str());
            instance.longtitude = atof(inst[3].c_str());
            instance.timestamp = parseTime(inst[4]);
            instance.sentiment = inst[5];
            instances.push_back(instance);
            ofile << "\t"<<instance.microblogid<<"|"<<parseHour(inst[4])<<"|"
                <<instance.lantitude<<"|"<<instance.longtitude<<"|";
            if(microfeature.find(instance.microblogid) == microfeature.end())
                ofile<<"0|0|false";
            else
                ofile<<microfeature[instance.microblogid];
        }
        ofile<<"\n";
    }
    ofile.close();
}

void computeFeature(string path, string result){
    int i = 0;
    ifstream file(path);
    string line;
    vector<string> row;
    vector<string> inst;
    //activity"\t"wordvector"\t"nextactivity_list"\t"instance_list
    ofstream ofile(result);
    ofile<<fixed;
    while(getline(file,line))
    {
        cout<<i++<<"\n";
        row = split(line, '\t');
        ofile<<row[0];
        double hour = 0;
        double lantitude = 0, longtitude = 0;
        double reposts_count = 0, comments_count = 0, favorited = 0;
        int count = row.size() - 1;
        for(int i = 1; i < row.size(); i++)
        {
            inst = split(row[i], '|');
            hour += atof(inst[1].c_str());
            lantitude += atof(inst[2].c_str());
            longtitude += atof(inst[3].c_str());
            reposts_count += atof(inst[4].c_str());
            comments_count += atof(inst[5].c_str());
        }
        ofile << "\t"<<count<<"\t"<<(hour / count)<<"\t"<<(lantitude / count)<<"\t"<<(longtitude / count)
            <<"\t"<<(reposts_count / count)<<"\t"<<(comments_count / count);
        ofile<<"\n";
    }
    ofile.close();
}

int main()
{
    string filterpath = "positive.txt";
    string jsonpath = "model.jsons";
    string allpath = "all_activity.txt";
    string centerpath = "res_all_200.txt";
    string savepath = "data/activities";
    string vectorpath = "vectors.txt";
    map<string, vector<NextActivity>> actnext;//for load in next
    map<string, vector<string>> actpoi;//for load in next
    map<string, map<string, int>> actuser;//for load in next
    map<string, vector<string>> center;//for load in center
    vector<Activity> activities;//for load in activities
    map<string, UUser> userinfo;//for load in userinfo
    map<string, int> filter;//index
    map<string, double> actid;//index
    map<string, double> userid;//index

    //copyFile("microblogs_with_geo.jsons","microblogs.jsons");
    //loadFeatureJson("microblogs_with_geo.jsons", "microblogs.txt");
    //loadAllActivityFeature("microblogs.txt", allpath, "microblogs_feature.txt");
    computeFeature("microblogs_feature.txt", "extract_feature.txt");
    /*loadFilter(filterpath, filter);
    cout<<"load filter done."<<endl;

    loadJson(jsonpath, actnext, actpoi, filter);
    cout<<"load json done."<<endl;

    loadAllActivity(allpath, activities, actuser, actpoi, filter);
    cout<<"load activity done."<<endl;

    loadCenter(centerpath, center);
    cout<<"load center done."<<endl;

    sae::io::GraphBuilder<double> builder;
    builder.AddVertexDataType("UUser");
    builder.AddVertexDataType("Activity");
    builder.AddVertexDataType("ActivityCenter");
    builder.AddEdgeDataType("Next");
    builder.AddEdgeDataType("CenterEdge");
    builder.AddEdgeDataType("UserEdge");

    double id = 1;
    for(vector<Activity>::iterator it  = activities.begin(); it != activities.end(); it++)
    {
        builder.AddVertex(id, *it, "Activity");
        //cout<<it->Name<<endl;
        actid[it->name] = id;
        id++;
    }
    cout<<"load Activity done."<< id <<endl;
    for(map<string, map<string, int>>::iterator it = actuser.begin(); it != actuser.end(); it++)
    {
        map<string, int> users = it->second;
        for(map<string, int>::iterator st  = users.begin(); st != users.end(); st++)
        {
            if(userid.find(st->first) == userid.end()){
                builder.AddVertex(id, UUser{st->first}, "UUser");
                userid[st->first] = id;
                id++;
            }
            if(actid[it->first] == 0)
                continue;
            builder.AddEdge(userid[st->first], actid[it->first], UserEdge{st->second},"UserEdge");
        }
    }
    cout<<"load user done."<<endl;
    for(map<string, vector<NextActivity>>::iterator it = actnext.begin(); it != actnext.end(); it++)
    {
        vector<NextActivity> next = it->second;
        for(vector<NextActivity>::iterator st  = next.begin(); st != next.end(); st++)
        {
            if(actid[st->name] == 0 || actid[it->first] == 0)
                continue;
            builder.AddEdge(actid[it->first], actid[st->name], Next{st->name, st->dur},"Next");
        }
    }
    cout<<"load next done."<<endl;
    for(map<string, vector<string>>::iterator it = center.begin(); it != center.end(); it++)
    {
        vector<string> points = it->second;
        builder.AddVertex(id, ActivityCenter{it->first}, "ActivityCenter");
        for(vector<string>::iterator st  = points.begin(); st != points.end(); st++)
        {
            if(actid[*st] != 0){
                builder.AddEdge(id, actid[*st], CenterEdge{1},"CenterEdge");
            }
        }
        id++;
    }
    cout<<"load center done."<<endl;

    builder.Save(savepath.c_str());
    cout<<"build graph done."<<endl;

    graph_type act_graph;
    act_graph.load_format("./data/activities");
    cout <<"Load Graph Done."<<endl;
    cout << "loaded n:" << act_graph.num_vertices() << ", m:" << act_graph.num_edges() << endl;

    string query;
    while(cin>>query)
    {
        double i = actid[query];
        cout<<i<<endl;
        Activity act = act_graph.vertex(i - 1).parse<Activity>();
        cout<<act;
    }*/

    // word2vec model = loadVector(vectorpath);
    // ofstream file("myvector.txt", ios::app);
    // for(map<string, int>::iterator it = model.Vocab.begin(); it != model.Vocab.end(); it++)
    // {
    //     vector<double> feature = model.getVector(it->second);
    //     file << it->first;
    //     for(int i = 0; i < feature.size(); i++)
    //         file << " " << feature[i];
    //     file << "\n";
    //     //load in model.jsons
    // }
    // file.close();
    // cout <<"Load vector Done."<<endl;

    // sae::io::MappedGraph* g = sae::io::MappedGraph::Open(savepath.c_str());
    // cout << "loaded, n: " << g->VertexCount() << ", m:" << g->EdgeCount() << endl;
    // for (auto vs = g->VerticesOfType("Activity"); vs->Alive(); vs->NextOfType()) {
    //     //std::cout << "here" << std::endl;
    //     Activity vd = sae::serialization::convert_from_string<Activity>(vs->Data());
    //     cout << vd.Name<< endl;
    // }
}

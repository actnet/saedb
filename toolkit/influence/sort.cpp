#include<utility>
#include<vector>
#include<algorithm>
using namespace std;

bool compare(const pair<int,int> &x, const pair<int,int> &y)
{
    return x.second > y.second;
}
extern void sort_pair(vector<pair<int,int>>& vec)
{
   sort(vec.begin(), vec.end(), compare);
}

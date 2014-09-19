
using namespace std;

template <typename T>
inline T parse(const string& data) {
    return sae::serialization::convert_from_string<T>(data);
}

struct Point{
	double x;
	double y;
};

class ActivityAnalysis{
public:
	string name;
	vector<Point> points;

public:
	void addPoint(double x, double y){
		Point point;
		point.x = x;
		point.y = y;
		points.push_back(point);
	}

	bool compare (Point i, Point j) { return i.x < j.x; }

	/*void SortPoint(){
		sort(points.begin(), points.end(), compare);
	}*/

	double compute(){
		double ave_x = 0, ave_y = 0;
		double all_x_y = 0;
		double all_x_2 = 0;
		for(int i = 0; i < points.size(); i++){
			ave_x += points[i].x;
			ave_y += points[i].y;
			all_x_y += points[i].x * points[i].y;
			all_x_2 += points[i].x * points[i].x;
		}
		ave_x = ave_x / points.size();
		ave_y = ave_y / points.size();
		double per = (all_x_y - points.size() * ave_x * ave_y) / (all_x_2 - points.size() * ave_x * ave_x);
		return per;
	}
};

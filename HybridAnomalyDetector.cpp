
/*
Name: Ron Harel
ID: 308433762
ex2
*/
#include "HybridAnomalyDetector.h"
#include <vector>
#include <map>
#include<string.h>

using namespace std;

HybridAnomalyDetector::HybridAnomalyDetector() {
	// TODO Auto-generated constructor stub
	

}

HybridAnomalyDetector::~HybridAnomalyDetector() {
	// TODO Auto-generated destructor stub
}

void HybridAnomalyDetector:: learnNormal(const TimeSeries& ts){
TimeSeries newTs = ts;
//TimeSeries newTs(ts);
//cout << "learn" << endl;
size_t len = newTs.getNumOfLine();
float maxCor = 0, cor = 0;
string maxCorFeature, maxFeatureName1, maxFeatureName2;
string feature1, feature2;
Point** points;
map<string, vector<float>> pearMap = newTs.getTable();
//cout << "pearsize" << endl;
//cout << pearMap.size() << endl;
for(int i = 0; i < newTs.getNumOfCol(); i++) {
	for(int j = i + 1; j < newTs.getNumOfCol(); j++) {
		
		feature1 = newTs.getFeaturesNames().at(i);
		feature2 = newTs.getFeaturesNames().at(j);
		cor = abs(pearson(pearMap.at(feature1).data(), 
		pearMap.at(feature2).data(), newTs.getNumOfLine()));
			
		if(cor > maxCor) {
			maxCorFeature = feature2;
			maxCor = cor;
			}

	}
	if (maxCor >= 0.9){
		SimpleAnomalyDetector :: learnNormalHelper(len, maxCor, feature1, maxCorFeature, pearMap);
       // cout << "learn3" << endl;
	}

	if (maxCor < 0.9 && maxCor >= 0.5) 
	{
		points = SimpleAnomalyDetector:: toPoints(pearMap.at(feature1), pearMap.at(maxCorFeature));
		HybridAnomalyDetector ::learnNormalHelper(len, maxCor, feature1, maxCorFeature, pearMap, points);
     //   cout << "learn2" << endl;
	}
	maxCor = 0;
}
//cout << "not" << endl;
}
void HybridAnomalyDetector::learnNormalHelper (size_t len, float core, string feature1, string feature2, map<string, vector<float>> pearMap, 
	Point** points){
	float radius;
	struct correlatedFeatures cr;
	cr.feature1 = feature1;
	cr.feature2 = feature2;
	cr.corrlation = core;
	radius = findMinCircle(points, pearMap.at(feature1).size()).radius;
	cr.x = findMinCircle(points, pearMap.at(feature1).size()).center.x;
	cr.y = findMinCircle(points, pearMap.at(feature1).size()).center.y;
	cr.threshold = radius *1.1;
	cf.push_back(cr);
}

vector<AnomalyReport> HybridAnomalyDetector:: detect(const TimeSeries& ts){
//	cout << "hybrid1" << endl;
	//TimeSeries newTs = ts;
    TimeSeries newTs(ts);
 //   cout << "hybrid" << endl;
	string feature;
	Point** point;
	float dis = 0;
	string description;
	long timeStep;
    
	vector <AnomalyReport> reportVec;
    
	map<string, vector<float>> pearMap = newTs.getTable();
 //   cout << "size" << endl;
   // cout << cf.size() << endl;
	for (int i = 0; i < cf.size(); i++) {
		if(cf.at(i).corrlation >= 0.9){
		reportVec = SimpleAnomalyDetector :: detect(ts);
     //   cout << "line" << endl;
		continue;
		} else if(cf.at(i).corrlation >= 0.5) {
      //      cout << "circle" << endl;

	for(int j = 0; j < newTs.getNumOfLine(); j++){
		for(int m = i; m < cf.size(); m++){
			
	Point p(pearMap.at(cf.data()[m].feature1).data()[j]
	, pearMap.at(cf.data()[m].feature2).data()[j]);
	Point p2(cf.data()[m].x, cf.data()[m].y);
	dis = dist(p, p2);
	
	if(dis > cf.data()[m].threshold){
	
		timeStep = j + 1;
        description = cf.data()[m].feature1 + '-' + cf.data()[m].feature2;
        AnomalyReport report(description , timeStep);	
        reportVec.push_back(report);
		}
	}
	}
}
}
	return reportVec;
} 

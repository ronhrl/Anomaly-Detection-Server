/*
Name: Ron Harel
ID: 308433762
ex2
*/

#include <vector>
#include <map>
#include<string.h>
#include "SimpleAnomalyDetector.h"
using namespace std;

SimpleAnomalyDetector::SimpleAnomalyDetector() {
	// TODO Auto-generated constructor stub
	this->threshold = 0.9;
}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {
	// TODO Auto-generated destructor stub
}

Point** SimpleAnomalyDetector::toPoints(vector<float> x, vector<float> y){
	Point** ps=new Point*[x.size()];
	for(size_t i=0;i<x.size();i++){
		ps[i]=new Point(x[i],y[i]);
	}
	return ps;
}

// void SimpleAnomalyDetector:: findCore(const TimeSeries& ts) {

// }

void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts){
TimeSeries newTs = ts;
size_t len = newTs.getNumOfLine();
float maxCor = 0, cor = 0;
//float* vector1, *vector2;
string maxCorFeature, maxFeatureName1, maxFeatureName2;
string feature1, feature2;
// struct correlatedFeatures cr;
map<string, vector<float>> pearMap = newTs.getTable();

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
	learnNormalHelper(len, maxCor, feature1, maxCorFeature, pearMap);
	// if(maxCor > threshold){
	// 	cr.feature1 = feature1;
	// 	cr.feature2 = maxCorFeature;
	// 	cr.corrlation = maxCor;
	// 	cr.lin_reg = linear_reg(pearMap.at(cr.feature1).data(), 
	// 	pearMap.at(cr.feature2).data(), newTs.getNumOfLine());

	// 	for(int t = 0; t < newTs.getNumOfLine(); t++) {
	// 		Point p(pearMap.at(cr.feature1).data()[t] , pearMap.at(cr.feature2).data()[t]);
	// 		dis = dev(p , cr.lin_reg);
	// 		if(dis > maxDis) {
	// 			maxDis = dis;
	// 			}
	// 			cr.threshold = 1.1 * maxDis;
	// 	}
	// 	maxCor = 0;
	// 	maxDis = 0;
	// 	cf.push_back(cr);
	// //}
	// }
}
}

float SimpleAnomalyDetector :: thresholdFinder(size_t len, map<string, vector<float>> pearMap, string feature1, string feature2, Line lin_reg) {
	float dis, maxDis = 0;
	for(size_t i = 0; i < len; i++) {
		Point p(pearMap.at(feature1).data()[i] , pearMap.at(feature2).data()[i]);
		dis = dev(p , lin_reg);
		if(dis > maxDis) {
			maxDis = dis;
			}
			//	cr.threshold = 1.1 * maxDis
			}
	return maxDis;
}


// in here i build the vector of CF
void SimpleAnomalyDetector :: learnNormalHelper(size_t len, float core, string feature1, string feature2, map<string, vector<float>> pearMap){
//TimeSeries newTs = ts;
if(core > threshold){
//	size_t len = newTs.getNumOfLine();
	struct correlatedFeatures cr;
	cr.feature1 = feature1;
	cr.feature2 = feature2;
	cr.corrlation = core;
	cr.lin_reg = linear_reg(pearMap.at(cr.feature1).data(), 
	pearMap.at(cr.feature2).data(), len);
	cr.threshold = thresholdFinder(len, pearMap, feature1, feature2, cr.lin_reg) * 1.1;
//		cout << "20" << endl;
	cf.push_back(cr);
}
}
	// TODO Auto-generated destructor stub


vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){
	TimeSeries newTs = ts;
	string feature;
	Point* point;
	float dis = 0;
	string description;
	long timeStep;
	vector <AnomalyReport> reportVec;
	map<string, vector<float>> pearMap = newTs.getTable();
    
	for(int i = 0; i < newTs.getNumOfLine(); i++) {
		for(int j = 0; j < cf.size(); j++) {
	Point p(pearMap.at(cf.data()[j].feature1).data()[i] 
	, pearMap.at(cf.data()[j].feature2).data()[i]);
    dis = dev(p , cf.data()[j].lin_reg);
    if (dis > cf.data()[j].threshold * 1.2){
        timeStep = i + 1;
        description = cf.data()[j].feature1 + '-' + cf.data()[j].feature2;
        AnomalyReport report(description , timeStep);
        reportVec.push_back(report);
        }
		}
	}
	return reportVec;
	// TODO Auto-generated destructor stub
}
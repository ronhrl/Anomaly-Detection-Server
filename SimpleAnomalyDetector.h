/*
Name: Ron Harel
ID: 308433762
ex2
*/
#ifndef SIMPLEANOMALYDETECTOR_H_
#define SIMPLEANOMALYDETECTOR_H_

#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"
#include "minCircle.h"
#include <vector>
#include <algorithm>
#include <string.h>
#include <math.h>
#include <iostream>
using namespace std;

struct correlatedFeatures{
	string feature1,feature2;  // names of the correlated features
	float corrlation;
	Line lin_reg;
	float threshold;
	//Point* center;
	//Circle circ;
	float x;
	float y;
	//float radius;
};


class SimpleAnomalyDetector:public TimeSeriesAnomalyDetector{
	protected:
	vector<correlatedFeatures> cf;
	float threshold;

public:
	SimpleAnomalyDetector();
	virtual ~SimpleAnomalyDetector();

	virtual void learnNormal(const TimeSeries& ts);
	virtual vector<AnomalyReport> detect(const TimeSeries& ts);

	vector<correlatedFeatures> getNormalModel(){
		return cf;
	}

	void setCorrelationThreshold(float threshold){
		this->threshold=threshold;
	}

	float getCorrelationThreshold(){
		return this->threshold;
	}

	// helper methods
protected:
	virtual void learnNormalHelper(size_t len, float core, string feature1, string feature2, map<string, vector<float>> pearMap);
	Point** toPoints(vector<float> x, vector<float> y);
	float thresholdFinder(size_t len, map<string, vector<float>> pearMap, string feature1, string feature2, Line lin_reg);

};

#endif /* SIMPLEANOMALYDETECTOR_H_ */

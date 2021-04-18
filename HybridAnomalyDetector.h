/*
Name: Ron Harel
ID: 308433762
ex2
*/

#ifndef HYBRIDANOMALYDETECTOR_H_
#define HYBRIDANOMALYDETECTOR_H_

#include "SimpleAnomalyDetector.h"
#include "minCircle.h"

class HybridAnomalyDetector:public SimpleAnomalyDetector {
public:
	HybridAnomalyDetector();
	virtual ~HybridAnomalyDetector();
	//virtual void learnNormalHelper();
	virtual void learnNormal(const TimeSeries& ts);
	virtual void learnNormalHelper(size_t len,
	 float core, string feature1, string feature2, map<string, vector<float>> pearMap, Point** points);
	virtual vector<AnomalyReport> detect(const TimeSeries& ts);
	vector<Point> toPoints(vector<float> x, vector<float> y);

};

#endif /* HYBRIDANOMALYDETECTOR_H_ */

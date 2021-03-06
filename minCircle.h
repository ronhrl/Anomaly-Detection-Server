
#ifndef MINCIRCLE_H_
#define MINCIRCLE_H_

#include "anomaly_detection_util.h"
#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h>

using namespace std;

// ------------ DO NOT CHANGE -----------
// class Point{
// public:
// 	float x,y;
// 	Point(float x,float y):x(x),y(y){}
// };

class Circle{
public:
	Point center;
	float radius;
	Circle(Point c,float r):center(c),radius(r){}
};
// --------------------------------------
float dist(Point a, Point b);
Circle trivalCircle2(Point a,Point b);
Circle trivalCircle3(Point a, Point b, Point c);
Circle trivial(vector<Point>& P);
Circle mindisc(Point** P,vector<Point> R, size_t n);
Circle findMinCircle(Point** points,size_t size);


#endif /* MINCIRCLE_H_ */

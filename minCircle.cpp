/*
Name: Ron Harel
ID: 308433762
ex2
*/
#include "minCircle.h"

float dist(Point a, Point b){
    return sqrt(pow(a.x-b.x, 2) + pow(a.y-b.y,2)); 
}

//making a circle out of 2 points
Circle trivalCircle2(Point p1,Point p2){
    float radius = dist (p1, p2) / 2;
	float cx = (p1.x + p2.x) / 2;
	float cy = (p1.y + p2.y) / 2;
	Point center(cx, cy);
    return Circle(center, radius);
}


//making a circle out of 3 points from Wikipdia
Circle trivalCircle3(Point p1, Point p2, Point p3){
    float bx = p2.x - p1.x;
	float by = p2.y - p1.y;
	float cx = p3.x - p1.x;
	float cy = p3.y - p1.y;

	float B = bx * bx + by * by; 
    float C = cx * cx + cy * cy; 
    float D = bx * cy - by * cx; 

	float centerX = (cy * B - by * C) / (2 * D) + p1.x;
	float centerY = (bx * C - cx * B) / (2 * D) + p1.y;

	Point center(centerX, centerY);

    float radius = dist(center, p1);

	return Circle(center, radius);
}

Circle trivial(vector<Point>& P){
	if(P.size()==0)
		return Circle(Point(0,0),0);
	else if(P.size()==1)
		return Circle(P[0],0);
	else if (P.size()==2)
		return trivalCircle2(P[0],P[1]);

	// maybe 2 of the points define a small circle that contains the 3ed point
	Circle c=trivalCircle2(P[0],P[1]);
	if(dist(P[2],c.center)<=c.radius)
		return c;
	c=trivalCircle2(P[0],P[2]);
	if(dist(P[1],c.center)<=c.radius)
		return c;
	c=trivalCircle2(P[1],P[2]);
	if(dist(P[0],c.center)<=c.radius)
		return c;
	// else find the unique circle from 3 points
	return trivalCircle3(P[0],P[1],P[2]);
}

//recursiv Wexler Algo
Circle mindisc(Point** P,vector<Point> R, size_t n){
	if(n==0 || R.size()==3){
		return trivial(R);
	}

	// remove random point p
	// swap is more efficient than remove
	//srand (time(NULL));
	int i=rand()%n;
	Point p(P[i]->x,P[i]->y);
	swap(P[i],P[n-1]);

	Circle c=mindisc(P,R,n-1);

	if(dist(p,c.center)<=c.radius)
		return c;

	R.push_back(p);

	return mindisc(P,R,n-1);
}

Circle findMinCircle(Point** points,size_t size){
	return mindisc(points,{},size);
}

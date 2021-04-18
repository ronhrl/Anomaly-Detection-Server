/*
Name: Ron Harel
ID: 308433762
*/
#include "anomaly_detection_util.h"
#include <cmath>
#include <iostream>
#include <stdlib.h>
using namespace std;

float avg(float* x, int size) {
    float pi=0, sum=0;
    for(int i=0; i < size; i++) {
        sum += x[i]; 
    }
    if (size * sum == 0) {
        return 0;
    }
    pi = (float) 1 / size * sum;
    return pi;
}

float var(float* x, int size) {
    float var1 , sumPow=0, pi = 0;
    for(int i=0; i < size; i++) {
          sumPow += pow(x[i] , 2);
    }        
    pi = avg(x , size);
        if (size * sumPow == 0) {
        return 0;
    }
    var1 = (float) 1 / size * sumPow - pow(pi , 2);
    return var1; 
}

float cov(float* x, float* y, int size) {
    float covarince = 0, sum = 0;
    for(int i = 0; i < size; i++) {
        sum += (x[i] - avg(x , size)) * (y[i] - avg(y , size));
    }

    covarince = sum / size;   
    return covarince;
}

float pearson(float* x, float* y, int size) {
    float pear = cov(x, y, size) / (sqrt(var(x , size)) * sqrt(var(y , size)));
    return pear; 
}

Line linear_reg(Point** points, int size){
    float a, b;
    float x[size], y[size];
    for(int i = 0; i < size; i++) {
        x[i] = points[i]->x;
        y[i] = points[i]->y;
    } 
    a = cov(x , y, size) / var(x , size);
    b = avg(y , size) - a * avg(x , size);
    return Line(a, b);  
}

Line linear_reg(float* x, float* y, int size) {
float a, b;
a = cov(x , y, size) / var(x , size);
b = avg(y , size) - a * avg(x , size);
return Line(a, b); 
}

float dev(Point p,Point** points, int size){
    float fx, dis;
    Line l = linear_reg(points , size);
    fx = l.f(p.x);
    dis = abs(fx - p.y);
return dis;

}

float dev(Point p,Line l) {
    float fx, dis;
    fx = l.f(p.x);
    dis = abs(fx - p.y);
  //  cout << "div1" << endl ;
return dis;
//return 0;
}
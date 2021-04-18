/*
Name: Ron Harel
ID: 308433762
ex2
*/
#include "timeseries.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <sstream>
#include <bits/stdc++.h>
#include <iterator>
#include <map>
using namespace std;


map<string, vector<float>> TimeSeries :: createTableFromFile(const char* CSVfileName){
    string skk = CSVfileName;
    fstream flightFile(skk);
    vector<string> paramLine;
    string lineOfParam, lineOfVal, param, val;
    vector<float> vecVal;

    getline(flightFile , lineOfParam);
    stringstream s(lineOfParam);

    while (getline(s, param, ','))
     {
     	vector<float> vecVal;
        this->featuresNames.push_back(param);
     	this->numOfCol++;
     	this->table.insert({param , vecVal});
     }
while(flightFile) {
	getline(flightFile , lineOfVal);
    stringstream s2(lineOfVal);
    int i = 0;
    while (getline(s2, val, ',')){
        this->table[featuresNames[i]].push_back(stof(val));
        i++;
    }
    this->numOfLines++;
}
   flightFile.close();
   return this->table;
}

std :: vector<string> TimeSeries :: getFeaturesNames(){
    return this->featuresNames;
}

std :: map<string, vector<float>> TimeSeries :: getTable(){
    return this->table;
}

float* TimeSeries :: getVals(string key){
    auto itr = this->table.find(key);
    float* vals;
    vals = itr->second.data();
    return vals;
}

void TimeSeries :: addParamToTable(char* param){
    vector<float> vecVal;
    this->table.insert({param , vecVal});
    this->numOfCol++;
}

int TimeSeries :: getNumOfCol() {
    return this->numOfCol;
}

int TimeSeries :: getNumOfLine() {
    return this->numOfLines;
}

void TimeSeries :: addNewLine(char* newFile) {
    fstream newFlight;
    string valLine;
    float val;
    newFlight.open(newFile , ios:: in | ios:: out);
    while(newFlight) {
        for(int i = 0; i < this->numOfCol; i++) {
            getline(newFlight , valLine);
            stringstream s2(valLine);
            s2>>val;
            //table.insert({lineOfParam[i], vecVal.push_back(val)});
            this->table[this->featuresNames[i]].push_back(val);
        }
    }
//	cout << "test7" << endl ;
    newFlight.close();
}

// char GetFeatureOfVariable(char* CSVfileName){
// 	return 0;
// }

float TimeSeries :: getValueOfVarByParam(string param, int numOfFlight) {
    float val;
    auto itr = this->table.find(param);
    val =  itr->second[numOfFlight];
//	cout << "test8" << endl ;
    return val;
}

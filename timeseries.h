/*
Name: Ron Harel
ID: 308433762
ex2
*/
#ifndef TIMESERIES_H_
#define TIMESERIES_H_
#include <vector>
#include <string.h>
#include <stdio.h>
#include <map>
#include <stdlib.h>
#include <iostream>
using namespace std;

class TimeSeries{

    const char* fileName;
    std :: vector<string> featuresNames;
    map<string, vector<float>> table;
    int numOfCol = 0;
    int numOfLines = -1;

public:

    map<string, vector<float>> createTableFromFile(const char* CSVfileName);

  //  TimeSeries(const char* CSVfileName) : fileName(CSVfileName), table(createTableFromFile(CSVfileName)) {};
    TimeSeries(const char* CSVfileName) {
  //    cout << "series" << endl;
        table = createTableFromFile(CSVfileName);
  };

    std :: vector<string> getFeaturesNames();

    std :: map<string, vector<float>> getTable();

    void addParamToTable(char* param);

    void addNewLine(char* newFile);

    int getNumOfLine();

    float getValueOfVarByParam(string param, int numOfFlight);

    int getNumOfCol();

    float* getVals(string key);

    // std :: map<string, vector<float>> createTableFromFile(const char* CSVfileName);

    // TimeSeries(const char* CSVfileName);

    // void AddFeatureToTable(char* CSVfileName);

    // char GetFeaturesNameFromTable(char* CSVfileName);

    // void AddLineToTable(char* CSVfileName);

    // char GetFeatureOfVariable(char* CSVfileName);

    // char GetFromCSV(char* CSVfileName);
};



#endif /* TIMESERIES_H_ */

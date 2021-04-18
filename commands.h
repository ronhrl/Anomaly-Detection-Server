/*
Name: Ron Harel
ID: 308433762
ex5
*/

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include <iostream>
#include "sstream"
#include <string.h>
#include <fstream>
#include <vector>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <thread>
#include <unistd.h>
#include "HybridAnomalyDetector.h"

using namespace std;

class mutualInfo{
    protected:
    TimeSeries* train;
    TimeSeries* test;
    HybridAnomalyDetector* hybridDetector;
    vector<AnomalyReport> anomalyReports;
    vector <int> reportsInt;

    public:

    mutualInfo(){
        this->hybridDetector = new HybridAnomalyDetector();
    }

    HybridAnomalyDetector* getHybrid(){
        return this->hybridDetector;
    }

    void setHybrid(HybridAnomalyDetector* hybridDet){
        this->hybridDetector = hybridDet;
    }

    TimeSeries* getTrain(){
        return this->train;
    }

    void setTrain(TimeSeries* newTrain) {
        this->train = newTrain;
    }

    void setTest(TimeSeries* newTest) {
        this->test = newTest;
    }

    void setTrain(TimeSeries newTrain){
        this->train = new TimeSeries(newTrain);
    }

    TimeSeries* getTest(){
        return this->test;
    } 

    void setTest(TimeSeries newTest){
        this->test = new TimeSeries(newTest);
    }

    vector<AnomalyReport> getAnomalys(){
        return this->anomalyReports;
    }

    void setAnomalys(vector <AnomalyReport> newReports){
        for (int i = 0; i < newReports.size(); i++){
            this->anomalyReports.push_back(newReports[i]);
        }
    }

    vector<int> combineReports(){
        vector<int> combReport;
        int count = 0, reportEnd = 0;
       // cout << 1 << endl;
        for(int i = 0; i < this->anomalyReports.size(); i = reportEnd + 1){
           // count = 0;
           // cout << 20 << endl;
           // cout << this->anomalyReports.size() << endl;
            for (int j = i+1; j < this->anomalyReports.size(); j++)
            {
           //     cout << j << endl;
                if(this->anomalyReports.at(i).description == this->anomalyReports.at(j).description){ 
                    //count ++;
                    // cout << this->anomalyReports.at(i).description << endl;
                    // cout << this->anomalyReports.at(j).description << endl;
                    reportEnd = j;
             //       cout << 3 << endl;
                }
                // else{
                //     break;
                // } 

            }
            // cout << this->anomalyReports.at(i).timeStep << endl;
            // cout << this->anomalyReports.at(reportEnd).timeStep << endl;
            combReport.push_back(this->anomalyReports.at(i).timeStep);
            combReport.push_back(this->anomalyReports.at(reportEnd).timeStep);
            // cout << "size" << endl;
            // cout << combReport.size() << endl;
           // cout << 9 << endl;
        }
    return combReport;
    }

    vector<int> reportStrToInt(vector <string> vec){
    vector<int> reportsInt;
    
    for(int i = 0; i < vec.size(); i++){
     string str = vec[i];
    string token;     
    istringstream tokenStream(str);     
    while (getline(tokenStream, token, ',')) {   
        try{
            reportsInt.push_back(stoi(token));
        }   
        catch (invalid_argument &){

        }
             
    }   
    }
    return reportsInt;
    }

    
};

class DefaultIO{
public:
    DefaultIO(){};
	virtual string read()=0;
	virtual void write(string text)=0;
	virtual void write(float f)=0;
	virtual void read(float* f)=0;
	virtual ~DefaultIO(){}
    virtual void fileUpload(string name) {};

	// you may add additional methods here
};

// you may add here helper classes

class StandardIO: public DefaultIO{
  public:
  StandardIO(): DefaultIO(){}

  virtual void read(float* f){
      cin >> *f;
  }

  virtual void write(float f){
      cout << f << endl;
  }

  virtual string read(){
      string str;
      cin >> str;
      return str;
  }

  virtual void write(string text) {
      cout << text << endl;
  }

      virtual void fileUpload(string name){
        fstream file(name);
        string line;

        do
        {
            getline(file, line);
            if(line != "done"){
                file << line << endl;
            }
        } while (line != "done");
        
        write("Upload complete.\n");
        if(file.is_open())
        file.close();
    }

};

class socketIO : public DefaultIO{
    int clientID;
    public:
        socketIO(int clientid){
            this->clientID = clientid;
        }

    virtual void read(float* f){
        float newF = *f;
		::read(clientID, &newF, sizeof(newF));

    }

    virtual void write(float f){
		string floatStr = to_string(f);
		while (floatStr.size() > 0 && floatStr[floatStr.size() - 1] == '0')
		{
			floatStr.pop_back();
		}
		write(floatStr);

    }

    virtual string read(){
		string str = "";
        char ch = 0;
        ::read(clientID, &ch, sizeof(char));
        while (ch != '\n') {
            str += ch;
            ::read(clientID, &ch, sizeof(char));
        }
        return str;

    }

    virtual void write(string text){
        ::write(clientID, text.c_str(), text.length());
    }

    int getClientId(){
        return this->clientID;
    }

    void setClientId(int newClientId){
        this->clientID = newClientId;
    }
};

// you may edit this class
class Command{
    protected:
	DefaultIO* dio;
    mutualInfo* info;
    string description;

public:
	Command(DefaultIO* dio, mutualInfo* info):dio(dio), info(info){}

    string getdescription(){
        return this->description;
    } 

    mutualInfo* getInfo(){
        return this->info;
    }

    DefaultIO* getDio(){
        return this->dio;
    }
    
    virtual void fileUpload(string name){
        ofstream file(name);
        string line;

        do
        {
            line = this->getDio()->read();
            if(line != "done"){
                file << line << endl;
            }
        } while (line != "done");
        
        this->getDio()->write("Upload complete.\n");
        if(file.is_open())
        file.close();
    }

    // int truePositiveCalc(vector<int> anomalyVec) {
    //     int sumOfAnomaly = 0, tp = 0, neg =0;
    //     vector<int> report;
    //     for(int i = 0; i < anomalyVec.size(); i+=2) {
    //             sumOfAnomaly += (anomalyVec.data()[i+1] - anomalyVec.data()[i]) + 1; 
    //         }
    //         neg = this->getInfo()->getTest()->getNumOfLine()- 1 - sumOfAnomaly;
          
    //         for (int j = 0; j < anomalyVec.size()-1; j += 2) {  
    //             for (int k = 0; k < report.size()-1; k += 2){
    //             if(report[k] <= anomalyVec[j] && report[k+1] <= anomalyVec[j+1] ||
    //             report[k] >= anomalyVec[j] && report[k+1] <= anomalyVec[j+1] ||
    //             report[k] >= anomalyVec[j] && report[k+1] >= anomalyVec[j+1])
    //             {
    //                 tp += 1;
    //             } 
    //         }
    //         }
    //     return tp;
    // }



	virtual void execute()=0;
	virtual ~Command(){}
};
class commandOne: public Command{
        public:

        commandOne(DefaultIO* dio, mutualInfo* data): Command(dio, data) {
            this->description = "1.upload a time series csv file\n";
        }

        void execute(){
            this->getDio()->write("Please upload your local train CSV file.\n");
            this->fileUpload("anomalyTrain.csv");
            this->getInfo()->setTrain(TimeSeries("anomalyTrain.csv"));

            this->getDio()->write("Please upload your local test CSV file.\n");
            this->fileUpload("anomalyTest.csv");
            this->getInfo()->setTest(TimeSeries("anomalyTest.csv"));

        }
    };

class commandTwo: public Command{
        public:

        commandTwo(DefaultIO* dio, mutualInfo* data): Command(dio, data) {
            this->description = "2.algorithm settings\n";
        }

        void execute(){

            string newThresStr;
            float newThresFloat;
            this->getDio()->write("The current correlation threshold is ");
            this->getDio()->write(this->getInfo()->getHybrid()->getCorrelationThreshold());
            this->getDio()->write("\n");

            this->getDio()->write("Type a new threshold\n");
            newThresStr = this->getDio()->read();
            
            newThresFloat = stof(newThresStr);

            if(newThresFloat > 1 || newThresFloat < 0) {
                this->getDio()->write("please choose a value between 0 and 1.\n");
                this->execute();
            }

            this->getInfo()->getHybrid()->setCorrelationThreshold(newThresFloat);

        }
    };

class commandThree: public Command{
        public:

        commandThree(DefaultIO* dio, mutualInfo* data): Command(dio, data) {
            this->description = "3.detect anomalies\n";
        }

        void execute(){

            this->getInfo()->getHybrid()->learnNormal(*this->getInfo()->getTrain());

            this->getInfo()->setAnomalys(this->getInfo()->getHybrid()->detect
            (*this->getInfo()->getTest())); 
            this->getDio()->write("anomaly detection complete.\n");
        }

    };

class commandFour: public Command{
        public:

        commandFour(DefaultIO* dio, mutualInfo* data): Command(dio, data) {
            this->description = "4.display results\n";
        }

        void execute(){
       

            for(int i = 0; i < this->getInfo()->getAnomalys().size(); i++){
            
            this->getDio()->write(this->getInfo()->getAnomalys().at(i).timeStep);
            this->getDio()->write("\t");
            this->getDio()->write(" ");
            this->getDio()->write(this->getInfo()->getAnomalys()[i].description);
       
            this->getDio()->write("\n");
            }
            this->getDio()->write("Done.\n");
        }
    
    };

class commandFive: public Command{
        public:

        commandFive(DefaultIO* dio, mutualInfo* data): Command(dio, data) {
            this->description = "5.upload anomalies and analyze results\n";
        }

        void execute(){ 
            this->getDio()->write("Please upload your local anomalies file.\n");
            vector <string> anomalysVec;
            vector <int> vecOfInt;
            vector <int> comb = this->getInfo()->combineReports();
            string anomalysLine = "";
            float P = 0 , truePositiveRate = 0, falsePositiveRate = 0, tp = 0, fp = 0;
            //cout << "zero" << endl;
            int sumOfAnomaly = 0, neg = 0;
            vector <string> hybridAnomalysVec;
            
            do
            {
                anomalysLine = this->getDio()->read();
                if(anomalysLine != "done") {
                    anomalysVec.push_back(anomalysLine);
                    
                }
            } while (anomalysLine != "done");

            this->getDio()->write("Upload complete.\n");

            P = anomalysVec.size();
            vecOfInt = this->getInfo()->reportStrToInt(anomalysVec);
            for(int i = 0; i < vecOfInt.size(); i+=2) {
                sumOfAnomaly += (vecOfInt.data()[i+1] - vecOfInt.data()[i]) + 1; 
            }

            //cout << sumOfAnomaly << endl;
            
            neg = this->getInfo()->getTest()->getNumOfLine() + 1 - sumOfAnomaly;
          
            //cout << neg << endl;
            // cout << "vecint" << endl;
            // cout << vecOfInt.size() << endl;;
            // cout << "comb" << endl;
            // cout << comb.size() << endl;
            // cout << "vecOfIntSize" << endl;
            // cout << vecOfInt.size() << endl;
            for (int j = 0; j < comb.size() - 1; j += 2) {  
              //  cout << 4 << endl;
                for (int k = 0; k < vecOfInt.size() - 1; k += 2){
             //       cout << 5 << endl;
                if((vecOfInt[k] >= comb[j] && vecOfInt[k] <= comb[j+1]) ||
                (vecOfInt[k+1] >= comb[j] && vecOfInt[k+1] <= comb[j+1]) ||
                 (comb[j] >= vecOfInt[k] && comb[j] <= vecOfInt[k+1]) ||
                (comb[j+1] >= vecOfInt[k] && comb[j+1] <= vecOfInt[k+1]))
                // if(this->getInfo()->getAnomalys()[k].timeStep >= vecOfInt[j]
                // && this->getInfo()->getAnomalys()[k].timeStep <= vecOfInt[j+1])
                {
                    // cout << "vec" << endl;
                    // cout << vecOfInt[k] << endl;
                    // cout << vecOfInt[k+1] << endl;
                    // cout << "comb" << endl;
                    // cout << comb[j] << endl;
                    // cout << comb[j+1] << endl;
                //    cout << "tp" << endl;
                    tp += 1;
                 }
                // else {
                // // cout << "fpElse" << endl;
                //  cout << "fp" << endl;  
                //  cout << k << endl;      
                //     fp += 1;
                //   //  break;
                // }
            }
            }
            
            //fp = this->getInfo()->getAnomalys().size() - tp;
            fp = comb.size()/2 - tp;
            // cout << "tp" << endl;
            // cout << tp << endl;
            // cout << "fp" << endl;
            // cout << fp << endl;
            // cout << "neg" << endl;
            // cout << neg << endl;
            truePositiveRate = tp/P;
            falsePositiveRate = fp/neg;
        
        if (truePositiveRate != 1){
        truePositiveRate = (float)(((int)(truePositiveRate*1000)) % 1000)/1000;    
        }
        if (falsePositiveRate != 1){
        falsePositiveRate = (float)(((int)(falsePositiveRate*1000)) % 1000)/1000;
        }

        this->getDio()->write("True Positive Rate: ");
        this->getDio()->write(truePositiveRate);
        this->getDio()->write("\n");

        this->getDio()->write("False Positive Rate: ");
        this->getDio()->write(falsePositiveRate);
        this->getDio()->write("\n");
        }

    };
class commandSix: public Command{
        public:

        commandSix(DefaultIO* dio, mutualInfo* data): Command(dio, data) {
            this->description = "6.exit\n";
        }

        void execute(){
        }

    };

// implement here your command classes



#endif /* COMMANDS_H_ */

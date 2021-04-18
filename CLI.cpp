/*
Name: Ron Harel
ID: 308433762
ex5
*/
#include "CLI.h"

CLI::CLI(DefaultIO* dio) {
    this->dio = dio;
    mutualInfo* info = new mutualInfo();
    info->setHybrid(this->hybridDetect);
    this->commandMap.insert({1,new commandOne(dio, info)});
    this->commandMap.insert({2,new commandTwo(dio, info)});
    this->commandMap.insert({3,new commandThree(dio, info)});
    this->commandMap.insert({4,new commandFour(dio, info)});
    this->commandMap.insert({5,new commandFive(dio, info)});
    this->commandMap.insert({6,new commandSix(dio, info)});
}

void CLI::start(){
    int commandNum = 0;
    string commandStr;

    while(commandNum != 6){
    this->dio->write("Welcome to the Anomaly Detection Server.\n");
    this->dio->write("Please choose an option:\n");

    for(int i = 1; i < this->commandMap.size() + 1; i++){
        this->dio->write(this->commandMap.find(i)->second->getdescription());
    }

    commandStr = this->dio->read();
  
    try {
        commandNum = stoi(commandStr);
        
        if(commandNum <= 6 && commandNum >= 1) {
      
        this->commandMap.at(commandNum)->execute();
        
}       
        else {
            break;
        }

    }
    catch (const invalid_argument&){

    }
    }
    }


CLI::~CLI() {
}


/*
Name: Ron Harel
ID: 308433762
ex5
*/

#ifndef CLI_H_
#define CLI_H_

#include <map>
#include <string.h>
#include "commands.h"

using namespace std;

class CLI {
	DefaultIO* dio;
    map <int, Command*> commandMap;
    HybridAnomalyDetector* hybridDetect = new HybridAnomalyDetector();
	// you can add data members
public:
	CLI(DefaultIO* dio);
	void start();
	virtual ~CLI();
};

#endif /* CLI_H_ */

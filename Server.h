/*
Name: Ron Harel
ID: 308433762
ex6
*/
/*
 * Server.h
 *
 *  Created on: Dec 13, 2020
 *      Author: Eli
 */

#ifndef SERVER_H_
#define SERVER_H_
#include "commands.h"
#include "CLI.h"


using namespace std;

// edit your ClientHandler interface here:
class ClientHandler{
    public:
    virtual void handle(int clientID)=0;
};


// you can add helper classes here and implement on the cpp file


// edit your AnomalyDetectionHandler class here
class AnomalyDetectionHandler:public ClientHandler{
	DefaultIO* dio;

	public:
    virtual void handle(int clientID){
	this->dio = new socketIO(clientID);

	CLI cli(this->dio);
	cli.start();
	
	}
};


// implement on Server.cpp
class Server {
	int stopConnection = 0;
	int fd;
	
	public:
	thread* t; // the thread to run the start() method in
	sockaddr_in server;
	sockaddr_in client;
	// you may add data members

public:
	Server(int port);
	virtual ~Server();
	void start(ClientHandler& ch);
	void stop();

		int getFd(){
		return this->fd;
	}

	void setFd(int newFd) {
		this->fd = newFd;
	}

	int getStopConnection(){
		return this->stopConnection;
	}

	void setStopConnection(int stCon){
		this->stopConnection = stCon;
	}
};

#endif /* SERVER_H_ */

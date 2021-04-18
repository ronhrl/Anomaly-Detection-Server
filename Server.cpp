/*
Name: Ron Harel
ID: 308433762
ex6
*/
#include<iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include "sstream"
#include "math.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include<pthread.h>
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Server.h"


Server::Server(int port) {
	this->setFd(socket(AF_INET, SOCK_STREAM, 0));
	if(this->getFd() < 0) {
		throw "socket failed";
	}
	this->server.sin_family = AF_INET;
	this->server.sin_addr.s_addr = INADDR_ANY;
	this->server.sin_port = htons(port);

	if(bind(this->getFd(), (struct sockaddr*)&server, sizeof(server)) < 0) {
		throw "bind failure";
	}

	if(listen(this->getFd() , 3) < 0){
		throw "listen failure";
	}
}

void Server::start(ClientHandler& ch){
	this->t = new thread([&ch, this](){ 
	socklen_t clientSize = sizeof(client);
	while (getStopConnection() == 0)
	{
	int aClient = accept(getFd(), (struct sockaddr*)&client, &clientSize);
	if(aClient < 0) {
		throw "accept failure";
	}
	ch.handle(aClient);
	close(aClient);
	}
	close(getFd());
	});	
}

void Server::stop(){
	this->stopConnection = 1;
	t->join(); // do not delete this!
}

Server::~Server() {
}


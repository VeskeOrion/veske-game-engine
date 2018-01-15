//----------------------------------------------------------------------------------------//
// GameLog.h
// A singleton class which is used to write essential game messages to a log or error file.
// These are currenly created in the directory of the executable. Such messages may be "Game
// started successfully." or "Game crashed!" etc. To use GameLog, simply include "GameLog.h"
// and use the following syntax:
// GameLog::log("An example log message!");
// GameLog::err("Oh no! An example error message!");
//----------------------------------------------------------------------------------------//


#ifndef LOGGER_H
#define LOGGER_H


#include <fstream>
#include <string>
#include <iostream>
#include <chrono>
#include <ctime>
#include <memory>
#include <iomanip>
#include <thread>

// TODO should I make this multithreaded so it can write to files without delaying game?
class Logger {
public:
	Logger();
	~Logger();

	bool init();

	//void close();

	//void log(const std::string & msg);
	//void err(const std::string & msg);

	//bool good;
	//std::ofstream logFile;
	//std::ofstream errFile;	
};

// Insert into Game::logger just like cout. Done use std::endl.
template <typename T>
std::unique_ptr<Logger> & operator<<(std::unique_ptr<Logger> & log, T  t) {
	//auto time = std::chrono::system_clock::now();
	//time_t time_t = std::chrono::system_clock::to_time_t(time);
				
	std::cout << t;
	//std::cout << "[LOG " << std::ctime(&time_t) << "] " << t;
	
	// TODO is this too slow?
	//if (log->good)
		//log->logFile /* << "[LOG " << std::ctime(&time_t) << "] " */ << t;
		
	return log;
}

#endif //GAMELOG_H
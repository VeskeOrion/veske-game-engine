//----------------------------------------------------------------------------------------//
// Logger.h
// Contains a class that generic messages can be written to. They will print to standard
// output, and can also be printed to a file at the same time (in development).
// Access this class via Game::logger, and use the << operator overload to insert strings,
// characters, integers, etc. into the output stream.
//----------------------------------------------------------------------------------------//


#ifndef LOGGER_H
#define LOGGER_H


#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <memory>
#include <chrono>
#include <ctime>
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
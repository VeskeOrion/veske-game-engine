//----------------------------------------------------------------------------------------//
// GameLog.cpp
// A singleton class which is used to write essential game messages to a log or error file.
// These are currenly created in the directory of the executable. Such messages may be "Game
// started successfully." or "Game crashed!" etc. To use GameLog, simply include "GameLog.h"
// and use the following syntax:
// Game::logger.log("An example log message!");
// Game::logger.err("Oh no! An example error message!");
//----------------------------------------------------------------------------------------//


#include "Logger.h"
#include "Game.h"

Logger::Logger() {

}


Logger::~Logger() {
	//close();
}


bool Logger::init() {
	//try {
		logFile.open("log.txt", std::ios::trunc);
	//	errFile.open("err.txt", std::ios::trunc);
	//}
	//catch (...) {
	//	good = false;
	//}
	//


	//good = (logFile.good() && errFile.good());

	//std::cout << std::setprecision(8);
	//if (good) {
	//	logFile << std::setprecision(8);
	//	errFile << std::setprecision(8);
	//}

	//return good;
	return true;
}


//void Logger::close() {
//	logFile.close();
//	errFile.close();
//}
//
//
//void Logger::log(const std::string & msg) {
//	auto time = std::chrono::system_clock::now();
//	time_t time_t = std::chrono::system_clock::to_time_t(time);
//
//	std::cout << "[LOG" /*<< std::ctime(&time_t) */ << "] " << msg << std::endl;
//
//	if (good)
//		logFile << "[LOG" /*<< std::ctime(&time_t) */ << "] " << msg << std::endl;
//}
//
//
//void Logger::err(const std::string & msg) {
//	auto time = std::chrono::system_clock::now();
//	time_t time_t = std::chrono::system_clock::to_time_t(time);
//
//	std::cout << "[ERR" /*<< std::ctime(&time_t) */ << "] " << msg << std::endl;
//
//	if (good)
//		errFile << "[ERR" /*<< std::ctime(&time_t) */ << "] " << msg << std::endl;
//}

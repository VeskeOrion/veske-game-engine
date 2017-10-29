//----------------------------------------------------------------------------------------//
// GameLog.cpp
// A singleton class which is used to write essential game messages to a log or error file.
// These are currenly created in the directory of the executable. Such messages may be "Game
// started successfully." or "Game crashed!" etc. To use GameLog, simply include "GameLog.h"
// and use the following syntax:
// GameLog::log("An example log message!");
// GameLog::err("Oh no! An example error message!");
//----------------------------------------------------------------------------------------//


#include "GameLog.h"




GameLog::GameLog() {
	_log.open("log.txt", std::ios::trunc);
	_err.open("err.txt", std::ios::trunc);
}

GameLog::~GameLog() {
	_log.close();
	_err.close();
}

GameLog& GameLog::getInstance() {
	static GameLog instance; // the single GameLog class
	return instance;
}

void GameLog::log(const std::string & msg) {
	getInstance()._log << msg << std::endl;

}

void GameLog::err(const std::string & msg) {
	getInstance()._err << msg << std::endl;
}

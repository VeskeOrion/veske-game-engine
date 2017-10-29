//----------------------------------------------------------------------------------------//
// GameLog.h
// A singleton class which is used to write essential game messages to a log or error file.
// These are currenly created in the directory of the executable. Such messages may be "Game
// started successfully." or "Game crashed!" etc. To use GameLog, simply include "GameLog.h"
// and use the following syntax:
// GameLog::log("An example log message!");
// GameLog::err("Oh no! An example error message!");
//----------------------------------------------------------------------------------------//


#ifndef GAMELOG_H
#define GAMELOG_H


#include <fstream>
#include <string>


class GameLog {
private:
	GameLog();
	~GameLog();
	GameLog(GameLog const&) = delete;
	void operator=(GameLog const&) = delete;

protected:
	static GameLog& getInstance();
	std::ofstream _log;
	std::ofstream _err;
	
public:
	static void log(const std::string &);
	static void err(const std::string &);
};

#endif //GAMELOG_H

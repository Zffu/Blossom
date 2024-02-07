#ifndef BLOSSOM_COMMONS_LOGGER
#define BLOSSOM_COMMONS_LOGGER

#include <string>
#include <iostream>

class Logger {
public:
	
	enum LogLevel {
		DEBUG,
		INFO,
		WARN,
		ERROR
	};

	std::string levelToString(LogLevel level) {
		switch (level)
		{
		case Logger::DEBUG:
			return "[Debug]";
		case Logger::INFO:
			return "[Info]";
		case Logger::WARN:
			return "[Warn]";
		case Logger::ERROR:
			return "[Error]";
		default:
			return "";
			break;
		}
	}

	static Logger& global() { static Logger logger; return logger; }

	void debug(std::string service, std::string msg) {
		if (enableDebug) {
			std::cout << generateLogMessage(service, msg, DEBUG);;
		}
	}

	void info(std::string service, std::string msg) {
		std::cout << generateLogMessage(service, msg, INFO);;
	}

	void warn(std::string service, std::string msg) {
		std::cout << generateLogMessage(service, msg, WARN);;
	}

	void error(std::string service, std::string msg) {
		std::cout << generateLogMessage(service, msg, ERROR);;
	}



private:
	bool enableDebug = false;
	bool showService = true;
	std::string mainPrefix = "[Blossom]";

	std::string generateLogMessage(std::string service, std::string msg, LogLevel level) {
		return mainPrefix + (showService ? '[' + service + "] " : " ") + levelToString(level) + ": " + msg;
	}
};

#endif

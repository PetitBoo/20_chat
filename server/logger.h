#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <mutex>
#include <thread>
#include <shared_mutex>


class Logger {
public:
	Logger();
	~Logger();
	void LoggerWrite(std::string message);
	void LoggerRead();
	std::ofstream file;

private:
	std::shared_mutex shared_mutex;
}

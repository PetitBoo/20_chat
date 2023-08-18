#include <iostream>
#include <fstream>
#include <sstream>
#include "logger.h"
#include <mutex>
#include <shared_mutex>
#include <thread>
#include <vector>


Logger::Logger()
{
		std::ofstream file("logger.txt", std::ios_base::out);
		if (file.is_open()) {
			file << "Logger is open.\n";
		}
}

Logger::~Logger()
{
	file.close();
}

void Logger::LoggerWrite(std::string message)
{
	shared_mutex.lock();
	file << message;
	shared_mutex.unlock();
}

void Logger::LoggerRead()
{
	shared_mutex.lock_shared();
	std::vector<std::string> outputs;
	std::ifstream file("logger.txt");
	std::string temp;
	while (std::getline(file, temp))
	{
		outputs.push_back(temp);
	}
	for (const auto& i : outputs)
		std::cout << i << std::endl;
	file.close();
	shared_mutex.unlock_shared();
}
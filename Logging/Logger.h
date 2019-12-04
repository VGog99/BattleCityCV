#pragma once
#include<iostream>
#include<string>
#ifdef LOGGING_EXPORTS
#define API_LOGGER __declspec(dllexport)
#else
#define API_LOGGER __declspec(dllimport)
#endif//LOGGING_EXPORTS
class API_LOGGER Logger
{
public:
	enum class Level
	{
		Debug,
		Info,
		Warning,
		Error
	};
private:
	std::ostream& m_out;

public:
	Level m_minLogLevel;
	Logger(std::ostream& out, Level minLogLevel = Level::Warning);
	void Log(const std::string& message, Level level);
	~Logger();
};


#pragma once
#include <ctime>
#include <iostream>
#include <iomanip>
#include<string>
#ifdef LOGGING_EXPORTS
#define API_LOGGER __declspec(dllexport)
#else
#define API_LOGGER __declspec(dllimport)
#endif//LOGGING_EXPORTS
#pragma warning(disable::4996)

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
	template<class ... Args>
	void Logi(Args&& ... params)
	{
		std::cout << "[Info]";
		std::time_t crtTime = std::time(nullptr);
		std::cout << '[' << std::put_time(std::localtime(&crtTime), "%Y-%m-%d %H:%M:%S") << ']';
		((std::cout << ' ' << std::forward<Args>(params)), ...);
		std::cout << '\n';
	}
	~Logger();
};


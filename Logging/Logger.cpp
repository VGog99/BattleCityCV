#include "Logger.h"



Logger::Logger(std::ostream& out, Level minLogLevel) :m_out(out), m_minLogLevel(minLogLevel)
{
}
void Logger::Log(const std::string& message, Level level)
{
	if (level < m_minLogLevel)
		return;
	m_out << message << "\n";
	switch (level)
	{
	case Logger::Level::Debug:
		m_out << "[Debug]";
		break;
	case Logger::Level::Info:
		m_out << "[Info]";
		break;
	case Logger::Level::Warning:
		m_out << "[Warning]";
		break;
	case Logger::Level::Error:
		m_out << "[Error]";
		break;
	}
	m_out << message << std::endl;
	//m_out.flush();
}
/*template<class ... Args>
void Logger::Logi(Args&& ... params)
{
	std::cout << "[Info]";
	std::time_t crtTime = std::time(nullptr);
	std::cout << '[' << std::put_time(std::localtime(&crtTime), "%Y-%m-%d %H:%M:%S") << ']';
	((std::cout << ' ' << std::forward<Args>(params)), ...);
	std::cout << '\n';
}*/

Logger::~Logger()
{
}
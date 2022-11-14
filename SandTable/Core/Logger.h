#pragma once
#include <spdlog/spdlog.h>

namespace SandTable 
{
	class Logger
	{
	public:
		static std::shared_ptr<spdlog::logger>& GetLogger();
		static void Init();

	private:
		Logger() {}
		Logger(const Logger&) = delete;
	private:
		static std::shared_ptr<spdlog::logger> m_spLogger;
	};
}

#define LOG_DEV_INFO(...)	::SandTable::Logger::GetLogger()->info(__VA_ARGS__)
#define LOG_DEVE_WARN(...)	::SandTable::Logger::GetLogger()->warn(__VA_ARGS__)
#define LOG_DEV_ERROR(...)	::SandTable::Logger::GetLogger()->error(__VA_ARGS__)


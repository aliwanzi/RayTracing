#include "Logger.h"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace SandTable 
{
	std::shared_ptr<spdlog::logger> Logger::m_spLogger;

	void Logger::Init()
	{
		//<1.创建多个sink
		auto spSink1 = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
		auto spSink2 = std::make_shared<spdlog::sinks::basic_file_sink_mt>("SandTable.log", true);
		std::vector<spdlog::sink_ptr> vecSinks = { spSink1,spSink2 };

		//<2.设置sink的pattern和level
		spSink1->set_pattern("%^[%T] %n: %v%$");
		spSink2->set_pattern("[%T] [%l] %n: %v");

		//<3.创建使用多个sink的单个logger，logger会把内容输出到不同位置，此处是控制台以及RotatingFileLog.txt
		m_spLogger = std::make_shared<spdlog::logger>("LoggerName", vecSinks.begin(), vecSinks.end());
		spdlog::register_logger(m_spLogger);
		m_spLogger->set_level(spdlog::level::trace);
		m_spLogger->flush_on(spdlog::level::trace);
	}

	std::shared_ptr<spdlog::logger>& Logger::GetLogger()
	{
		return m_spLogger;
	}
}


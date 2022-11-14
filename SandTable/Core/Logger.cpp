#include "Logger.h"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace SandTable 
{
	std::shared_ptr<spdlog::logger> Logger::m_spLogger;

	void Logger::Init()
	{
		//<1.�������sink
		auto spSink1 = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
		auto spSink2 = std::make_shared<spdlog::sinks::basic_file_sink_mt>("SandTable.log", true);
		std::vector<spdlog::sink_ptr> vecSinks = { spSink1,spSink2 };

		//<2.����sink��pattern��level
		spSink1->set_pattern("%^[%T] %n: %v%$");
		spSink2->set_pattern("[%T] [%l] %n: %v");

		//<3.����ʹ�ö��sink�ĵ���logger��logger��������������ͬλ�ã��˴��ǿ���̨�Լ�RotatingFileLog.txt
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


#pragma once
#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__

#include "common/SingletonT.hpp"
#include "boost/thread/thread.hpp"
#include "boost/thread/mutex.hpp"
#include <sstream>
#include <iostream>


#define LogInfo *(Robotarium::common::LoggerSet::GetSingleton()->logger_info)
#define LogWarn *(Robotarium::common::LoggerSet::GetSingleton()->logger_warn)
#define LogErr *(Robotarium::common::LoggerSet::GetSingleton()->logger_error)

namespace Robotarium
{
	namespace common
	{

		enum LogType
		{
			LOG_INFO,
			LOG_WARN,
			LOG_ERR
		};


		class LoggerTarget
		{
		public: virtual void inscribe(std::string _str, LogType _type){}
		};


		class Buffer : public std::stringbuf
		{

		public: Buffer(LoggerTarget* _target, LogType _type);

		public: Buffer(LogType _type);

		public: virtual ~Buffer();

		public: void SetTarget(LoggerTarget*);

		public: virtual int sync();

		public: LogType type;

		private: LoggerTarget* target;

		private: boost::mutex mMutex;

		};

		class Logger : public std::ostream
		{

		public: Logger(LoggerTarget* _target, LogType _type);

		public: Logger(LogType _type);

		protected: Buffer* buffer;

		public: void SetTarget(LoggerTarget*);

		private: LoggerTarget* target;



		};

		class LoggerSet : public SingletonT<LoggerSet>
		{
		public: LoggerSet(void);
			Logger* logger_info;
			Logger* logger_warn;
			Logger* logger_error;
		};

	}
}

#endif
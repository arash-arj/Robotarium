#include "common/Logger.hpp"

using namespace Robotarium;
using namespace common;



Buffer::~Buffer()
{
	this->pubsync();
}

int Buffer::sync()
{
	this->mMutex.lock();
	if(target)
		target->inscribe(this->str(), type);
	else
		std::cout << this->str();
	this->str("");
	this->mMutex.unlock();
	return 0;
}

Buffer::Buffer(LoggerTarget* _target, LogType _type)
	:  type(_type), target(_target)
{
}

Buffer::Buffer(LogType _type)
	:  type(_type)
{
}

Logger::Logger(LoggerTarget* _target, LogType _type)
	: std::ostream(buffer = new Buffer(_target, _type))
{
	this->setf(std::ios_base::unitbuf);
}

Logger::Logger(LogType _type)
	: std::ostream(buffer = new Buffer(0, _type)), target(0)
{
	this->setf(std::ios_base::unitbuf);
}


void Buffer::SetTarget(LoggerTarget* _target)
{
	target = _target;
}

void Logger::SetTarget(LoggerTarget* _target)
{
	target = _target;
	this->buffer->SetTarget(_target);
}

LoggerSet::LoggerSet(void)
{
	logger_info = new Logger(LOG_INFO);
	logger_warn = new Logger(LOG_WARN);
	logger_error = new Logger(LOG_ERR);
}
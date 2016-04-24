#include "common/Timer.hpp"

using namespace Robotarium;
using namespace common;


Timer::Timer()
{
	mInterval = 1;
}

Timer::~Timer()
{

}

void Timer::Stop()
{
	this->mDeadlineTimer->cancel();
}


void Timer::Start()
{
	mThread = boost::thread(&Timer::ServiceWorker, this);
}

void Timer::Init()
{	
	mIo = new boost::asio::io_service();
	mDeadlineTimer = new boost::asio::deadline_timer(*mIo);
}

void Timer::ServiceWorker()
{
	this->wait();
	mIo->run();
}

void Timer::wait()
{
	mDeadlineTimer->expires_from_now(boost::posix_time::milliseconds(this->mInterval));
	mDeadlineTimer->async_wait(boost::bind(&Timer::timeout, this, boost::asio::placeholders::error));
}


void Timer::SetHandler(boost::function<void()> _func)
{
	this->mHandler = _func;
}

void Timer::SetInterval(int _interval)
{
	this->mInterval = _interval;
}

void Timer::timeout(const boost::system::error_code &e) 
{
	if (e)
		return;
	wait();
	this->mHandler();
}
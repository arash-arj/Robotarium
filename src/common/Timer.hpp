#pragma once
#ifndef __TIMER_HPP__
#define __TIMER_HPP__

#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <functional>

namespace Robotarium
{
	namespace common
	{
		class Timer
		{
		public:		Timer();


		public:		~Timer();


		private:	boost::function<void()>	mHandler;


		public:		void Init();


		public:		void Start();


		public:		void Stop();


		public:		void Terminate();


		public:		void SetHandler(boost::function<void()> _func);


		public:		void SetInterval(int _interval);


		private:	void timeout(const boost::system::error_code &e);


		private:	boost::thread mThread;


		private:	void ServiceWorker();


		private:	boost::asio::io_service* mIo;


		private:	boost::asio::deadline_timer* mDeadlineTimer;


		private:	unsigned int mInterval;


		private:	void wait();
		};
	}
}

#endif
#pragma once
#ifndef __MANAGER_OUTPUT_HPP__
#define __MANAGER_OUTPUT_HPP__

#include "common/Types.hpp"

namespace Robotarium
{
	namespace core
	{
		class ManagerOutput;

		/// \def ManagerOutputPtr
		/// \brief Shared pointer to ManagerOutput
		typedef boost::shared_ptr<ManagerOutput> ManagerOutputPtr;

		class ManagerOutput
		{

		private:	std::vector<Robotarium::Signal> mPort;

		public:		Robotarium::Signal GetSignal(Robotarium::UInt32 _signal_index)
					{
						return this->mPort[_signal_index];
					}

		public:		void SetSignal(Robotarium::Signal _signal, Robotarium::UInt32 _signal_index)
					{
						this->mPort[_signal_index] = _signal;
					}


		public:		Robotarium::UInt32 GetPortSize()
					{
						return this->mPort.size();
					}

		public:		void SetPortSize(Robotarium::UInt32 _port_size)
					{
						this->mPort.resize(_port_size);
					}


		};

	}
}

#endif

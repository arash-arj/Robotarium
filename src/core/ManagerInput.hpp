#pragma once
#ifndef __MANAGER_INPUT_HPP__
#define __MANAGER_INPUT_HPP__

#include "common/Types.hpp"

namespace Robotarium
{
	namespace core
	{
		
		class ManagerInput
		{

		public:	virtual std::vector<Robotarium::Real> 
					GetValue(Robotarium::UInt32 _output_index) = 0;

		};

	}
}

#endif

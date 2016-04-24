#pragma once 
#ifndef __WINDOW_FACTORY_HPP__
#define __WINDOW_FACTORY_HPP__

#include "common/Types.hpp"

namespace Robotarium
{
	namespace graphic
	{

		class WindowFactory
		{
		public:		virtual Robotarium::String 
						CreateNewWindow(	Robotarium::Vec2 _viewportsize,
						Robotarium::String _name) = 0;
		};

		typedef boost::shared_ptr<WindowFactory> WindowFactoryPtr;
	}
}

#endif
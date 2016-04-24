#pragma once
#ifndef __VISITOR_HPP__
#define __VISITOR_HPP__

#include "SceneNode.hpp"

namespace Robotarium
{
	namespace core
	{
		class Visitor
		{
			
		public:		Visitor();

		public:		~Visitor();

		public:		virtual void Visit(Robotarium::core::NodePtr _node) = 0;
		};
	}
}

#endif
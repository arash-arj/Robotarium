#pragma once
#ifndef __COMMON_VISITORS_HPP__
#define __COMMON_VISITORS_HPP__

#include "core/Visitor.hpp"
#include "core/Node.hpp"

namespace Robotarium
{
	namespace common
	{
		class InitVisitor;

		class LoadVisitor;

		class UpdateVisitor;

		class TerminateVisitor;

		/// \def InitVisitorPtr
		/// \brief Shared pointer to InitVisitor
		typedef boost::shared_ptr<InitVisitor> InitVisitorPtr;

		/// \def LoadVisitorPtr
		/// \brief Shared pointer to LoadVisitor
		typedef boost::shared_ptr<LoadVisitor> LoadVisitorPtr;

		/// \def UpdateVisitorPtr
		/// \brief Shared pointer to UpdateVisitor
		typedef boost::shared_ptr<UpdateVisitor> UpdateVisitorPtr;

		/// \def TerminateVisitorPtr
		/// \brief Shared pointer to TerminateVisitor
		typedef boost::shared_ptr<TerminateVisitor> TerminateVisitorPtr;


		class InitVisitor : public core::Visitor
		{
		public:	InitVisitor(){}

		public:	~InitVisitor(){}

		public:	void Visit(Robotarium::core::NodePtr _node);
		};

		class LoadVisitor : public core::Visitor
		{
		public:	LoadVisitor(){}

		public:	~LoadVisitor(){}

		public:	void Visit(Robotarium::core::NodePtr _node);
		};

		class UpdateVisitor : public core::Visitor
		{
		public:	UpdateVisitor(){}

		public:	~UpdateVisitor(){}

		public:	void Visit(Robotarium::core::NodePtr _node);
		};

		class TerminateVisitor : public core::Visitor
		{
		public:	TerminateVisitor(){}

		public:	~TerminateVisitor(){}

		public:	void Visit(Robotarium::core::NodePtr _node);
		};

		
	}
}

#endif

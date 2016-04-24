#pragma once
#ifndef __NODE_HPP__
#define __NODE_HPP__

#include <vector>
#include <string>

#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include "common/Types.hpp"
#include "common/BaseObject.hpp"
#include "common/Logger.hpp"


namespace Robotarium
{
	namespace core
	{
		class Node : BaseObject
		{

		friend class core::Scene;

			/// \brief Constructor
			/// \param[in] name Name of the new Node
			/// \param[in] name A unique ID for the new Node
		public:		Node(Robotarium::String);

					/// \brief Destructor
		public:		~Node();

					/// \brief Set node type
		protected:	void SetNodeType(NODE_TYPE _type);

					/// \brief Get node type
		public:		NODE_TYPE GetNodeType();

					/// \brief Stores type of the node
		private:	NODE_TYPE type;

					/// \brief Returns the name of Node
		public:		Robotarium::String GetName();

					/// \brief Sets the name of Node
		protected:	void SetName(Robotarium::String);

					/// \brief Name of the Node
		private:	Robotarium::String mName;

					/// \brief Pointer to parent Node
		protected:	SceneNodePtr mParent;

					/// \brief Returns the pointer to parent node
		public:		SceneNodePtr GetParent();

					/// \brief Sets the parent node
		protected:	void SetParent(SceneNodePtr _parent_node);

					
					/// \brief Init this SceneNode and its children
		public:		virtual void Init() = 0;

					/// \brief Load this SceneNode and its children
		public:		virtual void Load() = 0;

					/// \brief Update this SceneNode and its children
		public:		virtual void Update() = 0;

					/// \brief Terminate this SceneNode and its children
		public:		virtual void Terminate() = 0;


		};
	}
}
#endif